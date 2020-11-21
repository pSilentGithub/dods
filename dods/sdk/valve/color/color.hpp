#pragma once

class color {
public:
	uint8_t m_r, m_g, m_b, m_a;

	color( uint8_t _r = 255, uint8_t _g = 255, uint8_t _b = 255, uint8_t _a = 255 ) : m_r( _r ), m_g( _g ), m_b( _b ), m_a( _a ) {
	}
};