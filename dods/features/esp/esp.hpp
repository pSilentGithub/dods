#pragma once

struct s_bounding_box {
	s_bounding_box( ) {
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
	}

	s_bounding_box( int x, int y, int w, int h ) {
		this->x = x;
		this->y = x;
		this->w = w;
		this->h = h;
	}
	int x, y, w, h;
};

class c_esp : public c_base_feature {
public:
	c_esp( ) {
		base_feature::features.push_back( this );
	}
private:
	void draw( );
	void players( );
public:
	bool get_bounding_box( c_base_entity* player, s_bounding_box& bounding_box );
}; extern c_esp* esp;