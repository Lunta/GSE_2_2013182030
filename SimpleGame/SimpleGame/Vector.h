#pragma once
#define ALLOWABLE_ERROR 0.00000001f

template<typename Ty>
struct Vector2D {
	Ty x, y;

	Vector2D() : x(0), y(0) {}
	Vector2D(Ty X, Ty Y) : x(X), y(Y) {}
	template<typename Ty1>
	Vector2D(Ty1 X, Ty1 Y, Ty1 Z) : x(static_cast<Ty>(X)), y(static_cast<Ty>(Y)) {}
	template<typename Ty1>
	Vector2D(const Vector2D<Ty1>& pt) : x(static_cast<Ty>(pt.x)), y(static_cast<Ty>(pt.y)) {}
	Vector2D& operator+=(const Vector2D& other) { x += other.x; y += other.y; return *this; }
	Vector2D& operator-=(const Vector2D& other) { x -= other.x; y -= other.y; return *this; }
	Vector2D& operator*=(const float f)			{ x *= f; y *= f; return *this; }
	Vector2D& operator=(const Ty(&other)[2])	{ x = other[0]; y = other[1]; return *this; }
	Vector2D& operator=(const Vector2D& other)	{ x = other.x; y = other.y; return *this; }
	bool operator==(const Vector2D& other) const { return { Length(other - *this) < ALLOWABLE_ERROR }; }
};
template<typename Ty> using Vec2D = Vector2D<Ty>;
using Vec2i = Vector2D<int>;
using Vec2f = Vector2D<float>;
using Vec2d = Vector2D<double>;

// Vec2D + Vec2D
template<typename Ty> inline Vec2D<Ty>	operator+(const Vec2D<Ty>& a, const Vec2D<Ty>& b)
{ return Vec2D<Ty>(a.x + b.x, a.y + b.y); }
// Vec2D - Vec2D
template<typename Ty> inline Vec2D<Ty>	operator-(const Vec2D<Ty>& a, const Vec2D<Ty>& b)
{ return Vec2D<Ty>(a.x - b.x, a.y - b.y); }

// float * Vec2D
template<typename Ty> inline Vec2D<Ty>	operator*(const float a, const Vec2D<Ty>& b)
{ return Vec2D<Ty>(a * b.x, a * b.y); }
// Vec2D * float
template<typename Ty> inline Vec2D<Ty>	operator*(const Vec2D<Ty>& a, const float b)
{ return Vec2D<Ty>(b * a.x, b * a.y); }

// Vec2D Length
template<typename Ty> inline float		Length(const Vec2D<Ty>& pd2dVec)
{ return(sqrt(pd2dVec.x * pd2dVec.x + pd2dVec.y * pd2dVec.y)); }
// Vec2D Normalize
template<typename Ty> inline Vec2D<Ty>& Normalize(Vec2D<Ty>& pd2dVec)
{ float fLength = Length(pd2dVec); if (fLength != 0) { pd2dVec.x /= fLength; pd2dVec.y /= fLength; } return pd2dVec; }
template<typename Ty> inline Vec2D<Ty>  CalcNormalize(const Vec2D<Ty>& pd2dVec)
{ float fLength = Length(pd2dVec); if (fLength != 0) { return Vec2D<Ty>{pd2dVec.x / fLength, pd2dVec.y / fLength}; } return Vec2D<Ty>(); }
// Vec2D Dot
template<typename Ty> inline float		operator*(const Vec2D<Ty>& a, const Vec2D<Ty>& b)
{ return float(a.x * b.x + a.y * b.y); }


template<typename Ty>
struct Vector3D 
{
	union {
		struct { Ty x, y, z; };
		struct { Ty r, g, b; };
		Ty arr[3];
	};

	Vector3D() : x(0), y(0), z(0) {}
	Vector3D(Ty X, Ty Y, Ty Z) : x(X), y(Y), z(Z) {}
	template<typename Ty1>
	Vector3D(Ty1 X, Ty1 Y, Ty1 Z) : x(static_cast<Ty>(X)), y(static_cast<Ty>(Y)), z(static_cast<Ty>(Z)) {}
	template<typename Ty1>
	Vector3D(const Vector3D<Ty1>& pt) : x(static_cast<Ty>(pt.x)), y(static_cast<Ty>(pt.y)), z(static_cast<Ty>(pt.z)) {}
	Vector3D& operator+=(const Vector3D& other) { x += other.x; y += other.y; z += other.z; return *this; }
	Vector3D& operator-=(const Vector3D& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	Vector3D& operator*=(const float f)			{ x *= f; y *= f; z *= f; return *this; }
	Vector3D& operator=(const Ty(&other)[3])	{ x = other[0]; y = other[1]; z = other[2]; return *this; }
	Vector3D& operator=(const Vector3D& other)	{ x = other.x; y = other.y; z = other.z; return *this; }
	bool operator==(const Vector3D& other) const { return { Length(other - *this) < ALLOWABLE_ERROR }; }
	
	Ty& operator[](size_t sz) {
		assert((sz < 0 || sz < 3) && "Vector3D 배열 범위 초과!");
		return arr[sz];
	}
};
template<typename Ty> using Vec3D = Vector3D<Ty>;
using Vec3f = Vector3D<float>;
using Vec3d = Vector3D<double>;
using Vec3i = Vector3D<int>;

// Vec3D + Vec3D
template<typename Ty> inline Vec3D<Ty>	operator+(const Vec3D<Ty>& a, const Vec3D<Ty>& b)	
{ return Vec3D<Ty>(a.x + b.x, a.y + b.y, a.z + b.z); }
// Vec3D - Vec3D
template<typename Ty> inline Vec3D<Ty>	operator-(const Vec3D<Ty>& a, const Vec3D<Ty>& b)	
{ return Vec3D<Ty>(a.x - b.x, a.y - b.y, a.z - b.z); }

// Array + Vec3D
template<typename Ty> inline Vec3D<Ty>	operator+(const Ty(&a)[3], const Vec3D<Ty>& b)		
{ return Vec3D<Ty>(a[0] + b.x, a[1] + b.y, a[2] + b.z); }
// Array - Vec3D
template<typename Ty> inline Vec3D<Ty>	operator-(const Ty(&a)[3], const Vec3D<Ty>& b)		
{ return Vec3D<Ty>(a[0] + b.x, a[1] + b.y, a[2] - b.z); }
// Vec3D + Array
template<typename Ty> inline Vec3D<Ty>	operator+(const Vec3D<Ty>& a, const Ty(&b)[3])		
{ return Vec3D<Ty>(a.x + b[0], a.y + b[1], a.z + b[2]); }
// Vec3D - Array
template<typename Ty> inline Vec3D<Ty>	operator-(const Vec3D<Ty>& a, const Ty(&b)[3])		
{ return Vec3D<Ty>(a.x - b[0], a.y - b[1], a.z - b[2]); }

// float * Vec3D
template<typename Ty> inline Vec3D<Ty>	operator*(const float a, const Vec3D<Ty>& b)	 	
{ return Vec3D<Ty>(a * b.x, a * b.y, a * b.z); }
// Vec3D * float
template<typename Ty> inline Vec3D<Ty>	operator*(const Vec3D<Ty>& a, const float b)	 	
{ return Vec3D<Ty>(b * a.x, b * a.y, b * a.z); }

// Vec3D Length
template<typename Ty> inline float		Length(const Vec3D<Ty>& pd3dVec)					
{ return(sqrt(pd3dVec.x * pd3dVec.x + pd3dVec.y * pd3dVec.y + pd3dVec.z * pd3dVec.z)); }
// Vec3D Normalize
template<typename Ty> inline Vec3D<Ty>& Normalize(Vec3D<Ty>& pd3dVec)						
{ float fLength = Length(pd3dVec); if (fLength != 0) { pd3dVec.x /= fLength; pd3dVec.y /= fLength; pd3dVec.z /= fLength; } return pd3dVec; }
template<typename Ty> inline Vec3D<Ty>  CalcNormalize(const Vec3D<Ty>& pd3dVec)				
{ float fLength = Length(pd3dVec); if (fLength != 0) { return Vec3D<Ty>{pd3dVec.x / fLength, pd3dVec.y / fLength, pd3dVec.z / fLength}; } return Vec3D<Ty>(); }
// Vec3D Dot
template<typename Ty> inline float		operator*(const Vec3D<Ty>& a, const Vec3D<Ty>& b)	
{ return float(a.x * b.x + a.y * b.y + a.z * b.z); }
// Vec3D Cross
template<typename Ty> inline Vec3D<Ty>	Cross(const Vec3D<Ty>& a, const Vec3D<Ty>& b)		
{ return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }


template <typename Ty>
struct Vector4D {
	union {
		struct { Ty x, y, z, w; };
		struct { Ty r, g, b, a; };
		Ty arr[4];
	};

	Vector4D() : x(0), y(0), z(0), w(0) {}
	Vector4D(Ty X, Ty Y, Ty Z, Ty W) : x(X), y(Y), z(Z), w(W) {}
	template<typename Ty1>
	Vector4D(Ty1 X, Ty1 Y, Ty1 Z, Ty1 W) : x(static_cast<Ty>(X)), y(static_cast<Ty>(Y)), z(static_cast<Ty>(Z)), w(static_cast<Ty>(W)) {}
	template<typename Ty1>
	Vector4D(const Vector4D<Ty1>& pt) : x(static_cast<Ty>(pt.x)), y(static_cast<Ty>(pt.y)), z(static_cast<Ty>(pt.z)), w(static_cast<Ty>(pt.w)) {}
	Vector4D& operator+=(const Vector4D& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
	Vector4D& operator-=(const Vector4D& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
	Vector4D& operator*=(const float f) { x *= f; y *= f; z *= f; w *= f; return *this; }
	Vector4D& operator=(const Ty(&other)[4]) { x = other[0]; y = other[1]; z = other[2]; w = other[3]; return *this; }
	Vector4D& operator=(const Vector4D& other) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }
	bool operator==(const Vector4D& other) const { return { Length(other - *this) < ALLOWABLE_ERROR }; }

	Ty& operator[](size_t sz) {
		assert((sz < 0 || sz < 4) && "Vector4D 배열 범위 초과!");
		return arr[sz];
	}
};
template<typename Ty> using Vec4D = Vector4D<Ty>;
using Vec4i = Vector4D<int>;
using Vec4f = Vector4D<float>;
using Vec4d = Vector4D<double>;

// Vec4D + Vec4D
template<typename Ty> inline Vec4D<Ty>	operator+(const Vec4D<Ty>& a, const Vec4D<Ty>& b)
{ return Vec4D<Ty>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
// Vec4D - Vec4D
template<typename Ty> inline Vec4D<Ty>	operator-(const Vec4D<Ty>& a, const Vec4D<Ty>& b)
{ return Vec4D<Ty>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }

// Array + Vec4D
template<typename Ty> inline Vec4D<Ty>	operator+(const Ty(&a)[4], const Vec4D<Ty>& b)
{ return Vec4D<Ty>(a[0] + b.x, a[1] + b.y, a[2] + b.z, a[3] + b.w); }
// Array - Vec4D
template<typename Ty> inline Vec4D<Ty>	operator-(const Ty(&a)[4], const Vec4D<Ty>& b)
{ return Vec4D<Ty>(a[0] + b.x, a[1] + b.y, a[2] - b.z, a[3] - b.w); }
// Vec4D + Array
template<typename Ty> inline Vec4D<Ty>	operator+(const Vec4D<Ty>& a, const Ty(&b)[4])
{ return Vec4D<Ty>(a.x + b[0], a.y + b[1], a.z + b[2], a.w + b[3]); }
// Vec4D - Array
template<typename Ty> inline Vec4D<Ty>	operator-(const Vec4D<Ty>& a, const Ty(&b)[4])
{ return Vec4D<Ty>(a.x - b[0], a.y - b[1], a.z - b[2], a.w - b[3]); }

// float * Vec4D
template<typename Ty> inline Vec4D<Ty>	operator*(const float a, const Vec4D<Ty>& b)
{ return Vec4D<Ty>(a * b.x, a * b.y, a * b.z, a * b.w); }
// Vec4D * float
template<typename Ty> inline Vec4D<Ty>	operator*(const Vec4D<Ty>& a, const float b)
{ return Vec4D<Ty>(b * a.x, b * a.y, b * a.z, b * a.w); }

// Vec4D Length
template<typename Ty> inline float		Length(const Vec4D<Ty>& pd4dVec)
{ return(sqrt(pd4dVec.x * pd4dVec.x + pd4dVec.y * pd4dVec.y + pd4dVec.z * pd4dVec.z)); }
// Vec4D Normalize
template<typename Ty> inline Vec4D<Ty>& Normalize(Vec4D<Ty>& pd4dVec)
{ float fLength = Length(pd4dVec); if (fLength != 0) { pd4dVec.x /= fLength; pd4dVec.y /= fLength; pd4dVec.z /= fLength; } return pd4dVec; }
template<typename Ty> inline Vec4D<Ty>  CalcNormalize(const Vec4D<Ty>& pd4dVec)
{ float fLength = Length(pd4dVec); if (fLength != 0) { return Vec4D<Ty>{pd4dVec.x / fLength, pd4dVec.y / fLength, pd4dVec.z / fLength}; } return Vec4D<Ty>(); }
// Vec4D Dot
template<typename Ty> inline float		operator*(const Vec4D<Ty>& a, const Vec4D<Ty>& b)
{ return float(a.x * b.x + a.y * b.y + a.z * b.z); }
// Vec4D Cross
template<typename Ty> inline Vec4D<Ty>	Cross(const Vec4D<Ty>& a, const Vec4D<Ty>& b)
{ return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }
