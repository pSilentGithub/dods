#pragma once

class c_base_feature {
public:
	virtual void draw( ) = 0;
};

namespace base_feature {
	extern std::vector<c_base_feature*> features;
}