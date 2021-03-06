// renderer.h

#ifndef renderer_h
#define renderer_h

#include <vector>

#include "boundary_base.h"
#include "glm_headers.h"
#include "particle_system.h"
#include "shader_program.h"
#include "obj_model.h"

namespace pbf {
class ArcballCamera;
class ParticleSystem;

class SceneRenderer {
public:
  SceneRenderer() = default;
  SceneRenderer(const SceneRenderer &) = delete;
  SceneRenderer &operator=(const SceneRenderer &) = delete;

  void SetWorldSize(const vec_t &s);

  void SetCamera(pbf::ArcballCamera *camera);

  void SetParticleSystem(pbf::ParticleSystem *ps);

  void SetPespectiveProjection(float fov, float wh_aspect, float near,
                               float far);

  // |obj_model| must exist during the lifetime of this object!
  void RegisterObjModel(const ObjModel* obj_model);
  
  // TOOD: we might need to have multiple shader programs in the future, so
  // this function signature should be deprecated
  void InitShaders(const char *vert_path, const char *frag_path);

  void InitSpriteShaders(const char *vert_path, const char *frag_path);

  void InitScene();

  void Render();


private:
  void SetVao(GLuint vao, GLuint vbo, GLuint ebo) const;

  void PrepareBoundaryBuffers();
  
  void PrepareObjModelsBuffers();

  void UpdateBoundaryAt(size_t i);

  void UpdateObjModelsPositions();
  
  pbf::ArcballCamera *camera_;
  pbf::ParticleSystem *ps_;
  std::vector<const ObjModel*> obj_models_;
  // OpenGL transformation matrices
  glm::mat4 model_;
  glm::mat4 proj_;

  // default shaders
  ShaderProgram shader_program_;
  ShaderProgram sprite_shader_program_;

  // *world* is a cube that defines the boundary of the PBF.
  GLfloat world_sz_x_;
  GLfloat world_sz_y_;
  GLfloat world_sz_z_;
  // world boundary
  GLuint boundaries_vao_;
  GLuint boundaries_vbo_;
  GLuint boundaries_ebo_;

  std::vector<GLfloat> boundary_vertices_;
  std::vector<GLuint> boundary_indices_;

  // xyz frame (coordinate)
  GLuint frame_vao_;
  GLuint frame_vbo_;
  GLuint frame_ebo_;

  std::vector<GLfloat> frame_vertices_;
  std::vector<GLuint> frame_indices_;

  // registered object models
  GLuint obj_models_vao_;
  GLuint obj_models_vbo_;
  GLuint obj_models_ebo_;

  std::vector<GLfloat> obj_models_vertices_;
  std::vector<GLuint> obj_models_indices_;

  // particles
  GLuint particles_vao_;
  GLuint particles_vbo_;
  GLuint particles_ebo_;

  std::vector<GLfloat> particle_vertices_;
  std::vector<GLuint> particle_indices_;

  ////////////////////////////////////////////////////
  // fluid rendering
  GLuint fluid_fbo_;
  GLuint fluid_texture_;
  GLuint fluid_rbo_;

public:
  // public for quick implementation
  struct BoundaryRecord {
    size_t index;
    float v1_len;
    float v2_len;
  };
  std::vector<BoundaryRecord> boundary_records_;
  BoundaryConstraintBase *boundary_constraint_;
};
} // namespace pbf

#endif // renderer_h
