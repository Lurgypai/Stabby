#pragma once
#include "AABB.h"

class EditorCam {
public:
	EditorCam(int id_);
	void update();
private:
	int id;
	AABB staticBox;
};