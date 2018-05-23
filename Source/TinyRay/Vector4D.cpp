#include <math.h>

#include "Vector4D.h"

Vector4D::Vector4D(const Vector4D& rhs)
{
	m_element[0] = rhs[0];
	m_element[1] = rhs[1];
	m_element[2] = rhs[2];
	m_element[3] = rhs[3];
}

double Vector4D::operator [] (const int i) const
{
	return m_element[i];
}

double& Vector4D::operator [] (const int i)
{
	return m_element[i];
}

Vector4D Vector4D::operator + (const Vector4D& rhs) const
{
	return Vector4D(
		(*this)[0] + rhs[0],
		(*this)[1] + rhs[1],
		(*this)[2] + rhs[2],
		(*this)[3] + rhs[3]);
}

Vector4D Vector4D::operator - (const Vector4D& rhs) const
{
	return Vector4D(
		(*this)[0] - rhs[0],
		(*this)[1] - rhs[1],
		(*this)[2] - rhs[2],
		(*this)[3] - rhs[3]);
}

Vector4D& Vector4D::operator = (const Vector4D& rhs)
{
	m_element[0] = rhs[0];
	m_element[1] = rhs[1];
	m_element[2] = rhs[2];
	m_element[3] = rhs[3];
	return *this;
}

Vector4D Vector4D::operator * (const Vector4D& rhs) const
{
	return Vector4D(
		m_element[0] * rhs[0],
		m_element[1] * rhs[1],
		m_element[2] * rhs[2],
		m_element[3] * rhs[3]);
}

Vector4D Vector4D::operator * (double scale) const
{
	return Vector4D(
		m_element[0] * scale,
		m_element[1] * scale,
		m_element[2] * scale,
		m_element[3] * scale
		);
}

double Vector4D::Norm_Sqr() const
{
	return m_element[0] * m_element[0] + m_element[1] * m_element[1] + m_element[2] * m_element[2];
}

Vector4D Vector4D::ToInHomogeneousVector() const
{
	double inv_homo = 1.0 / m_element[3];

	return Vector4D(m_element[0] * inv_homo, m_element[1] * inv_homo, m_element[2] * inv_homo, 1.0);
}

double Vector4D::Length() const
{
	return sqrtf(m_element[0] * m_element[0]
		+ m_element[1] * m_element[1]
		+ m_element[2] * m_element[2]
		+ m_element[3] * m_element[3]);
}

double Vector4D::LengthSqr() const
{
	return m_element[0] * m_element[0]
		+ m_element[1] * m_element[1]
		+ m_element[2] * m_element[2]
		+ m_element[3] * m_element[3];
}

double Vector4D::DotProduct(const Vector4D& rhs) const
{
	// assuming the homogeneous element is 1.0

	return m_element[0] * rhs[0] + m_element[1] * rhs[1] + m_element[2] * rhs[2] + m_element[3] * rhs[3];
}

Vector4D Vector4D::Normalise()
{
	double length = this->Length();

	if (length > 1.0e-8f)
	{
		double invLen = 1.0f / length;

		m_element[0] *= invLen;
		m_element[1] *= invLen;
		m_element[2] *= invLen;
		m_element[3] *= invLen;
	}

	return *this;
}

Vector4D Vector4D::CrossProduct(const Vector4D& rhs) const
{
	return Vector4D(
		(m_element[1] * rhs[2] - m_element[2] * rhs[1]),
		(m_element[2] * rhs[0] - m_element[0] * rhs[2]),
		(m_element[0] * rhs[1] - m_element[1] * rhs[0]),
		1.0f
		);
}

void Vector4D::SetZero()
{
	m_element[0] = m_element[1] = m_element[2] = m_element[3] = 0.0f;
}
