#include "../Headers/SpriteBatch.h"
#include "../Headers/Errors.h"

#include <algorithm>

namespace Celofan{

    SpriteBatch::SpriteBatch(): _vbo(0), _vao(0) {

    }

    SpriteBatch::~SpriteBatch() {

    }

    void SpriteBatch::init() {
        createVertexArray();
    }

    void SpriteBatch::begin(GlyphSortType sortType) {
        _sortType = sortType;
        _renderBatches.clear();
        for(Glyph* g : _glyphs){
            delete g;
        }
        _glyphs.clear();
    }

    void SpriteBatch::end() {
        sortGlyphs();
        createRenderBatches();
    }

    void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color) {

        Glyph* newGlyph = new Glyph;
        newGlyph->texture = texture;
        newGlyph->depth = depth;

        newGlyph->topLeft.color = color;
        newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
        newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

        newGlyph->bottomLeft.color = color;
        newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
        newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

        newGlyph->topRight.color = color;
        newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
        newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

        newGlyph->bottomRight.color = color;
        newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
        newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

        _glyphs.push_back(newGlyph);
    }

    void SpriteBatch::renderBatch() {

        glBindVertexArray(_vao);

        for (int i = 0; i < _renderBatches.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
            glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
        }

        glBindVertexArray(0);
    }

    void SpriteBatch::createRenderBatches() {

        // Create a vector to store all the vertices that they are going to be rendered
        // and resize it to allocate the memory that we are going to need.
        std::vector<Vertex> vertices;
        vertices.resize(_glyphs.size() * 6);

        // Check if we have any sprite.
        if(_glyphs.empty()){
            return;
        }

        // Init the offset and the current vertex index to 0.
        int offset = 0;
        int cv = 0; //Current vertex

        // Create a new render batch with the first sprite in the glyph list
        _renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);

        // Add all the vertex of the sprite to the Vertex vector.
        vertices[cv++] = _glyphs[0]->topLeft;
        vertices[cv++] = _glyphs[0]->bottomLeft;
        vertices[cv++] = _glyphs[0]->bottomRight;
        vertices[cv++] = _glyphs[0]->bottomRight;
        vertices[cv++] = _glyphs[0]->topRight;
        vertices[cv++] = _glyphs[0]->topLeft;
        offset +=6;

        // Add the rest of the sprites, if the nex sprite uses the same texture
        // increase the number of vertex in the last render batch, else create a new
        // render batch with the data of the current sprite.
        for(int cg = 1; cg < _glyphs.size(); cg++){
            if(_glyphs[cg]->texture != _glyphs[cg-1]->texture){
                _renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
            }else{
                _renderBatches.back().numVertices +=6;
            }
            // Add all the vertex of the sprite to the Vertex vector.
            vertices[cv++] = _glyphs[cg]->topLeft;
            vertices[cv++] = _glyphs[cg]->bottomLeft;
            vertices[cv++] = _glyphs[cg]->bottomRight;
            vertices[cv++] = _glyphs[cg]->bottomRight;
            vertices[cv++] = _glyphs[cg]->topRight;
            vertices[cv++] = _glyphs[cg]->topLeft;
            offset += 6;
        }

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }

    void SpriteBatch::createVertexArray() {

        if(_vao == 0){
            glGenVertexArrays(1, &_vao);
        }
        glBindVertexArray(_vao);

        if(_vbo == 0){
            glGenBuffers(1, &_vbo);
        }
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        // Vertex position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));

        // Vertex color attribute
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *) offsetof(Vertex, color));

        // Vertex uv attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, uv));

        glBindVertexArray(0);
    }

    void SpriteBatch::sortGlyphs() {
        switch (_sortType){
            case GlyphSortType::BACK_TO_FRONT :
                std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
                break;
            case GlyphSortType::FRONT_TO_BACK :
                std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
                break;
            case GlyphSortType::TEXTURE :
                std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
                break;
        }
    }

    bool SpriteBatch::compareFrontToBack(Glyph *a, Glyph *b) {
        return (a->depth < b->depth);
    }

    bool SpriteBatch::compareBackToFront(Glyph *a, Glyph *b) {
        return (a->depth > b->depth);
    }

    bool SpriteBatch::compareTexture(Glyph *a, Glyph *b) {
        return (a->texture < b->texture);
    }

}