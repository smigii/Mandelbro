#pragma once

typedef long double ldouble;

ldouble map(ldouble val, ldouble from_min, ldouble from_max, ldouble to_min, ldouble to_max)
{
	return (val - from_min) * (to_max - to_min) / (from_max - from_min) + to_min;
}