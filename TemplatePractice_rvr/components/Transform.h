#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "../ecs/Component.h"

#include "../utils/Vector2D.h"

class Transform : public Component {
public:
	Transform() : pos_(), vel_(), width_(), height_(), rotation_() {}

	Transform(Vector2D pos, Vector2D vel, float width, float height,
		float rotation) : pos_(pos), vel_(vel), width_(width), height_(height), rotation_(rotation) {}

	virtual ~Transform() {}

	inline Vector2D& getPos() { return pos_; }

	inline Vector2D& getVel() { return vel_; }

	inline float getH() const { return height_; }

	inline void setH(float height) { height_ = height; }

	inline float getW() const { return width_; }

	inline void setW(float width) { width_ = width; }

	inline float getRot() const { return rotation_; }

	inline void setRot(float rot) { rotation_ = rot; }

	void update() override { pos_ = pos_ + vel_; }

private:
	Vector2D pos_;
	Vector2D vel_;

	float width_;
	float height_;
	float rotation_;
};
#endif