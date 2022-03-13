#include "Phy2dFunc.h"

#include "TransformComponent.h"
#include "Phy2DComponent.h"
#include "CameraComponent.h"

#include "box2d.h"

#include "ShaderProgram.h"

#include "RenderFunc.h"


namespace fl {

void Phy2dFunc::SyncPhyAndTransform(const WCPhy2DSettings* phy2dSettings, Entity* entity)
{
    auto trans = entity->GetComponent<TransformComponent>();
    auto phy2d = entity->GetComponent<Phy2DComponent>();
        
    
    // apply pos
    const b2Vec2& pos = phy2d->GetBody()->GetPosition();
    trans->SetX(pos.x);
    trans->SetY(pos.y);
    
    
    if(phy2d->_bodyType == Phy2DComponent::BodyType::Static)
    {
//        trans->SetRotationZ(30);
    }
    // @miao @todo
    // apply angle
    trans->SetRotationZ(glm::degrees(phy2d->GetBody()->GetAngle()));
}

void Phy2dFunc::DrawDebugWire(ShaderManager* shaderManager,const WCPhy2DSettings* phy2dSettings,Phy2DComponent* phy2d,CameraComponent* cam)
{
    auto transform = phy2d->GetEntity()->GetComponent<TransformComponent>();
    
    // prepare
    glPointSize(20);
    
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glDisable(GL_DEPTH_TEST);
    ShaderProgram* shader = shaderManager->GetShader((unsigned int)EBuiltinShaderId::Builtin_Phy2dDebug);
    shader->Use();
    
//    RenderUtil::HandleMVP(shader,transform, cam->GetEntity()->GetComponent<TransformComponent>(), cam);
    
    if(shader->CheckUniform("u_Model"))
    {
        glm::vec3 pos = transform->_pos;
        glm::vec3 scale = transform->_scale;

        glm::mat4 model = RenderUtil::CalcModelMatrix(pos,scale,transform->_rotByEachAxis);
        shader->SetUniformMat4x4("u_Model", &model[0][0]);
    }
    
    RenderUtil::HandleVP(shader, cam->GetEntity()->GetComponent<TransformComponent>(), cam);
    glBindVertexArray(phy2d->_vao);
    glDrawElements(GL_LINES,(int)phy2d->_indicesData.size(),GL_UNSIGNED_INT,0);
    
    glBindVertexArray(0);
    shader->UnUse();
}

}
