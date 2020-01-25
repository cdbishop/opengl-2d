#include "TextManager.hpp"

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include <sstream>

#include <glm/gtc/type_ptr.hpp>

struct Character {
  GLuint TextureID;
  glm::ivec2 Size;
  glm::ivec2 Bearing;
  GLuint Advance;
};

class FTManager {
public:
  FTManager() {
    if (FT_Init_FreeType(&_ft) != 0) {
      throw std::runtime_error("Failed to init FreeType Library");
    }
  }

  ~FTManager() { FT_Done_FreeType(_ft); }

  void LoadFont(const std::string& file, unsigned int size) {
    FT_Face face;
    if (FT_New_Face(_ft, file.c_str(), 0, &face) != 0) {
      std::stringstream ss;
      ss << "Failed to load file " << file << " as font face";
      throw std::runtime_error(ss.str());
    }

    FT_Set_Pixel_Sizes(face, 0, size);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte c = 0; c < face->num_glyphs; ++c) {
      if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
        throw std::runtime_error("Failed to load glyph");
      }

      // create texture for character
      GLuint texture;
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
        face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer);
      // Set texture options
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      Character character = {
          texture,
          glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
          glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
          face->glyph->advance.x };

      _characters[c] = character;
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);

    _font_map[file] = face;
  }

  float CalculateStringLength(const std::string& text, float scale) {
    float length = 0.0f;
    for (auto c = text.begin(); c != text.end(); ++c) {
      auto ch = GetChar(*c);
      length += (ch.Advance >> 6) * scale;
    }

    return length;
  }

  const Character& GetChar(GLchar character) const { return _characters.at(character); }

private:
  FT_Library _ft;
  std::map<std::string, FT_Face> _font_map;
  std::map<GLchar, Character> _characters;
};

TextManager::TextManager(std::shared_ptr<ShaderManager> shaderManager,
  glm::mat4 projection)
  : _shader(shaderManager->CreateProgram("text", "text")),
  _projection(std::move(projection)),
  _ft_manager(std::make_shared<FTManager>()) {
  _ft_manager->LoadFont(
    "data/textures/SpaceShooterRedux/Bonus/kenvector_future.ttf", 48);

  glGenVertexArrays(1, &_vertex_array);
  glGenBuffers(1, &_vertex_buffer);
  glBindVertexArray(_vertex_array);
  glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

TextManager::~TextManager() {}

TextManager::Id TextManager::AddText(std::string text, glm::vec2 position,
  float scale, glm::vec3 colour) {
  _texts.push_back(
    { std::move(text), std::move(position), std::move(colour), scale });
  return _texts.size() - 1;
}

void TextManager::RemoveText(Id id) { _texts.erase(_texts.begin() + id); }

void TextManager::UpdateText(Id id, std::string newValue) {
  _texts[id].value = newValue;
}

void TextManager::Render() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(_vertex_array);

  glUseProgram(_shader->GetId());

  _shader->SetUniformValue("inTexture", 0);
  _shader->SetUniformValuePtr("projection", glm::value_ptr(_projection));

  for (auto&& text : _texts) {
    GLfloat cursor_x = 0.0f;

    float length = _ft_manager->CalculateStringLength(text.value, text.scale);
    float half_length = length / 2.0f;

    _shader->SetUniformValue("textColor", text.colour);

    for (auto c = text.value.begin(); c != text.value.end(); ++c) {
      Character ch = _ft_manager->GetChar(*c);

      GLfloat xpos =
        text.position.x + cursor_x + ch.Bearing.x * text.scale - half_length;
      GLfloat ypos = text.position.y - (ch.Size.y - ch.Bearing.y) * text.scale;

      GLfloat width = ch.Size.x * text.scale;
      GLfloat height = ch.Size.y * text.scale;

      GLfloat vertices[6][4] = {
          {xpos, ypos, 0.0f, 0.0f},
          {xpos, ypos + height, 0.0f, 1.0f},
          {xpos + width, ypos + height, 1.0f, 1.0f},

          {xpos, ypos, 0.0f, 0.0f},
          {xpos + width, ypos + height, 1.0f, 1.0f},
          {xpos + width, ypos, 1.0f, 0.0f},
      };

      glBindTexture(GL_TEXTURE_2D, ch.TextureID);
      glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      glDrawArrays(GL_TRIANGLES, 0, 6);

      // advance the start of next character by size of current
      cursor_x += (ch.Advance >> 6) * text.scale;
    }
  }

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);

  glDisable(GL_BLEND);
}
