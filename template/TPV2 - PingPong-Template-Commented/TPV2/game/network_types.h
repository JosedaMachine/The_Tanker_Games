// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_net.h>
#include <iostream>

#pragma pack(push,1)

// print an IPv4
inline void print_ip(Uint32 ip, bool newline = false) {
	std::cout << (ip & 0xFF) << "." //
			<< ((ip >> 8) & 0xFF) << "." //
			<< ((ip >> 16) & 0xFF) << "." //
			<< ((ip >> 24) & 0xFF);
	if (newline)
		std::cout << std::endl;
}

// these are the classical functions for converting
// host to network integers and vice versa. Apparently
// there is no common library that works on all OS. They
// basically use SDLNet_Write and SDLNet_Read but have an
// API similar to the original ones.

inline Uint32 sdlnet_htonl(Uint32 v) {
	Uint32 nv;
	SDLNet_Write32(v, &nv);
	return nv;
}

inline Uint32 sdlnet_ntohl(Uint32 nv) {
	return SDLNet_Read32(&nv);
}

inline Uint16 sdlnet_htons(Uint16 v) {
	Uint16 nv;
	SDLNet_Write16(v, &nv);
	return nv;
}

inline Uint16 sdlnet_ntohs(Uint16 nv) {
	return SDLNet_Read16(&nv);
}

// numeric type that can be transmitted over
// a connection. Internally they keep the value
// using network format (big Endian) and whenever
// the value is used it is converted to little
// Endian. They are based on using the functions
// above. They do not have constructor on purpose,
// so they can be easily used in union types
//
//   uint32_nt
//   int32_nt
//   uint16_nt
//   int16_nt
//   uint8_nt    -- just aliased to Uint8
//   int8_nt
//   float32_nt  -- asserts that float is 32bit, and some other stuff
//

// for Uint32
struct uint32_nt {

	inline uint32_nt& operator=(Uint32 v) {
		v_ = sdlnet_htonl(v);
		return *this;
	}

	inline operator Uint32() {
		return sdlnet_ntohl(v_);
	}

private:
	Uint32 v_;
};

// for Sint32
// ==========
//
// We transmit the sign and the unsigned value and construct it back, this is the safest
// we could do. A more efficient is to cast to Uint32 and back to Sint32, but for this
// we have to make sure that both machine use the same representation for negative
// numbers, e.g., Two's complement (which is most likely true as it is use almost everywhere)
//
struct int32_nt {

	inline int32_nt& operator=(Sint32 v) {
		if (v < 0) {
			s_ = 1;
			v_ = sdlnet_htonl(static_cast<Uint32>(-v));
		} else {
			s_ = 0;
			v_ = sdlnet_htonl(static_cast<Uint32>(v));
		}
		return *this;
	}

	inline operator Sint32() {
		Sint32 v = static_cast<Sint32>(sdlnet_ntohl(v_));
		if (s_ == 1)
			v = -v;
		return v;
	}

private:
	Uint32 v_;
	Uint8 s_;
};

// for Uint16
// ==========
//
struct uint16_nt {

	inline uint16_nt& operator=(Uint16 v) {
		v_ = sdlnet_htons(v);
		return *this;
	}

	inline operator Uint16() {
		return sdlnet_ntohs(v_);
	}

private:
	Uint16 v_;
};

// for Sint16
// ==========
//
// We transmit the sign and the unsigned value and construct it back, this is the safest
// we could do. A more efficient is to cast to Uint32 and back to Sint32, but for this
// we have to make sure that both machine use the same representation for negative
// numbers, e.g., Two's complement (which is most likely true as it is use almost everywhere)
//
struct int16_nt {

	inline int16_nt& operator=(Sint16 v) {
		if (v < 0) {
			s_ = 1;
			v_ = sdlnet_htons(static_cast<Uint16>(-v));
		} else {
			s_ = 0;
			v_ = sdlnet_htons(static_cast<Uint16>(v));
		}
		return *this;
	}

	inline operator Sint16() {
		Sint16 v = static_cast<Sint16>(sdlnet_ntohs(v_));
		if (s_ == 1)
			v = -v;
		return v;
	}

private:
	Uint16 v_;
	Uint8 s_;
};

// for Uint8
// =========
//
typedef Uint8 uint8_nt;

// for Sint8
// =========
//
// We transmit the sign and the unsigned value and construct it back, this is the safest
// we could do. A more efficient is to cast to Uint32 and back to Sint32, but for this
// we have to make sure that both machine use the same representation for negative
// numbers, e.g., Two's complement (which is most likely true as it is use almost everywhere)
//
struct int8_nt {

	inline int8_nt& operator=(Sint8 v) {
		if (v < 0) {
			s_ = 1;
			v_ = static_cast<Uint8>(-v);
		} else {
			s_ = 0;
			v_ = static_cast<Uint8>(v);
		}
		return *this;
	}

	inline operator Sint16() {
		Sint16 v = static_cast<Sint16>(v_);
		if (s_ == 1)
			v = -v;
		return v;
	}

private:
	Uint8 v_;
	Uint8 s_;
};

// for float
// =========
//
// just an attempt based on the representation in:
//
//   https://sites.uclouvain.be/SystInfo/usr/include/ieee754.h.html
//
// there seem no standards for how floating point are
// represented using big-endian and little-endian
//
// we assume that a float is represented as in ieee754, i.e.,
// the order of its parts is
//
//   Big-Endian     :  Sign Exp Mantisa
//   Little-Endian  :  Mantisa Exp Sign
//
// where Sign is a 1-bit, Exp is an unsigned integer of 8bit, and
// Mantisa is unsigned integer of 23 bit. The bytes of each unsigned
// integer follows the corresponding Endiannes
//
// We transmit the different parts and construct them back.
//
struct float32_nt {

	static_assert( sizeof(float) == 4, "float is not 32 bits");

	// ieee754 float on big endian
	typedef union {
		float value;
		struct {
			Uint32 sign :1;
			Uint32 exponent :8;
			Uint32 mantissa :23;
		};
	} IEEE_754_float_big_endian;
	static_assert( sizeof(IEEE_754_float_big_endian) == 4, "IEEE_754_float_big_endian is not 4 bytes, something is wrong with packing");

	// ieee754 float on little endian
	typedef union {
		float value;
		struct {
			Uint32 mantissa :23;
			Uint32 exponent :8;
			Uint32 sign :1;
		};
	} IEEE_754_float_little_endian;

	static_assert( sizeof(IEEE_754_float_little_endian) == 4, "IEEE_754_float_little_endian is not 4 bytes, something is wrong with packing");

	inline float32_nt& operator=(float v) {
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
		IEEE_754_float_little_endian f = { };
		f.value = v;
		m_ = sdlnet_htonl(f.mantissa);
		e_ = f.exponent;
		s_ = f.sign;
#else
		IEEE_754_float_big_endian f = { };
		f.value = v;
		m_ = f.mantissa;
		e_ = f.exponent;
		s_ = f.sign;
#endif
		return *this;
	}

	inline operator float() {
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
		IEEE_754_float_little_endian f = { };
		f.mantissa = sdlnet_ntohl(m_);
		f.exponent = e_;
		f.sign = s_;
#else
		IEEE_754_float_big_endian f = { };
		f.mantissa = m_;
		f.exponent = e_;
		f.sign = s_;
#endif
		return f.value;
	}

private:
	Uint32 m_;
	Uint8 e_;
	Uint8 s_;
};


#pragma pack(pop)
