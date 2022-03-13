#include "Phy2dFunc.h"

#include "TransformComponent.h"
#include "Phy2DComponent.h"

#include "box2d.h"


namespace fl {

void Phy2dFunc::SyncPhyAndTransform(const WCPhy2DSettings* phy2dSettings, Entity* entity)
{
    auto trans = entity->GetComponent<TransformComponent>();
    auto phy2d = entity->GetComponent<Phy2DComponent>();
    
    /*
     物理与显示的比例
     比如 一个屏幕 在 orho 的 情况下，假设 上下显示范围是 [-1,1]
     上下能容纳 50 个物理单位
     则这个值是 (1 - (-1)) / 50 = 0.04
     **/
//    float Ratio() const { return _ratio;}
//    float _ratio = 0.04;
    
    const b2Vec2& pos = phy2d->GetBody()->GetPosition();
    trans->SetX(pos.x * phy2dSettings->Ratio());
    trans->SetY(pos.y * phy2dSettings->Ratio());
    
    
}

}
