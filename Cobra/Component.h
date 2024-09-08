#pragma once
struct Component {
	int id;
	int mask;
};

struct MeshComponent:Component {
	id = 0;
	mask = 1;
};