#ifndef ANIMATION_DIRECTIONAL_H
#define ANIMATION_DIRECTIONAL_H

#include "SpriteManager.h"
#include "AnimationBase.h"
class AnimationDirectional :
	public AnimationBase
{
public:

protected:
	void frameStep() override;
	void cropSprite() override;
	void readIn(const std::stringstream& stream) override;

private:

};
#endif // !ANIMATION_DIRECTIONAL_H
