#ifndef renderer_h
#define renderer_h

#include <GL/glew.h>
#include <vector>

#include "glm_headers.h"
#include "particle_system.h"

namespace pbf {
    class ArcballCamera;
    class ParticleSystem;
    
    class SceneRenderer {
    public:
        SceneRenderer() = default;
        SceneRenderer(const SceneRenderer&) = delete;
        SceneRenderer& operator=(const SceneRenderer&) = delete;
        
        void SetWorldSize(const vec_t& s);
        
        void SetCamera(pbf::ArcballCamera* camera);
        
        void SetParticleSystem(pbf::ParticleSystem* ps);
       
        void SetPespectiveProjection(float fov, float wh_aspect, float near, float far);
        
        void InitShaders(const char* vert_path, const char* frag_path);
        
        void InitScene();
        
        void Render();
        
        void SetVao_(GLuint vao, GLuint vbo, GLuint ebo) const;
    private:
        
        pbf::ArcballCamera* camera_;
        pbf::ParticleSystem* ps_;
        
        // OpenGL transformation matrices
        glm::mat4 model_;
        glm::mat4 proj_;
        
        GLuint shader_program_;
        // *world* is a cube that defines the boundary of the PBF.
        // It is not the rendering stage.
        GLfloat world_sz_x_;
        GLfloat world_sz_y_;
        GLfloat world_sz_z_;
        
        GLuint world_vao_;
        GLuint world_vbo_;
        GLuint world_ebo_;
        
        std::vector<GLfloat> world_cube_vertices_;
        std::vector<GLuint> world_cube_indices_;
        // xyz frame (coordinate) 
		GLuint frame_vao_;
        GLuint frame_vbo_;
        GLuint frame_ebo_;
        
        std::vector<GLfloat> frame_vertices_;
        std::vector<GLuint> frame_indices_;
        // particles
        GLuint particles_vao_;
        GLuint particles_vbo_;
        GLuint particles_ebo_;
        
        std::vector<GLfloat> particle_vertices_;
        std::vector<GLuint> particle_indices_;
		
    };
} // namespace pbf

#endif // renderer_h
