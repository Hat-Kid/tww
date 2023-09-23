//
// Generated by dtk
// Translation Unit: c_angle.cpp
//

#include "SSystem/SComponent/c_angle.h"
#include "dolphin/types.h"

extern f32 cM_atan2f(f32, f32);

const cSAngle cSAngle::_0(static_cast<s16>(0));
const cSAngle cSAngle::_1(static_cast<s16>(0xb6));
const cSAngle cSAngle::_90(static_cast<s16>(0x4000));
const cSAngle cSAngle::_180(static_cast<s16>(-0x8000));
const cSAngle cSAngle::_270(static_cast<s16>(-0x4000));

/* 80253BB0-80253BE0       .text __ct__7cSAngleFRC7cSAngle */
cSAngle::cSAngle(const cSAngle& angle) {
    Val(angle);
}

/* 80253BE0-80253C10       .text __ct__7cSAngleFs */
cSAngle::cSAngle(s16 angle) {
    Val(angle);
}

/* 80253C10-80253C40       .text __ct__7cSAngleFf */
cSAngle::cSAngle(f32 angle) {
    Val(angle);
}

/* 80253C40-80253C4C       .text Val__7cSAngleFRC7cSAngle */
void cSAngle::Val(const cSAngle& other) {
    mAngle = other.mAngle;
}

/* 80253C4C-80253C54       .text Val__7cSAngleFs */
void cSAngle::Val(s16 val) {
    mAngle = val;
}

/* 80253C54-80253C78       .text Val__7cSAngleFf */
void cSAngle::Val(f32 degree) {
    mAngle = cAngle::Degree_to_SAngle(degree);
}

/* 80253C78-80253CAC       .text Degree__7cSAngleCFv */
f32 cSAngle::Degree() const {
    return cAngle::SAngle_to_Degree(mAngle);
}

/* 80253CAC-80253CE0       .text Radian__7cSAngleCFv */
f32 cSAngle::Radian() const {
    return cAngle::SAngle_to_Radian(mAngle);
}

/* 80253CE0-80253D14       .text Norm__7cSAngleCFv */
f32 cSAngle::Norm() const {
    return cAngle::SAngle_to_Normal(mAngle);
}

/* 80253D14-80253D30       .text Abs__7cSAngleCFv */
s16 cSAngle::Abs() const {
    return mAngle >= 0 ? mAngle : -mAngle;
}

/* 80253D30-80253D40       .text Inv__7cSAngleCFv */
s16 cSAngle::Inv() const {
    return mAngle - 0x8000;
}

/* 80253D40-80253D68       .text Sin__7cSAngleCFv */
f32 cSAngle::Sin() const {
    return sin(Radian());
}

/* 80253D68-80253D90       .text Cos__7cSAngleCFv */
f32 cSAngle::Cos() const {
    return cos(Radian());
}

/* 80253D90-80253DB8       .text Tan__7cSAngleCFv */
f32 cSAngle::Tan() const {
    return tan(Radian());
}

/* 80253DB8-80253DE4       .text __mi__7cSAngleCFv */
cSAngle cSAngle::operator-() const {
    return cSAngle(static_cast<s16>(-mAngle));
}

/* 80253DE4-80253E14       .text __pl__7cSAngleCFRC7cSAngle */
cSAngle cSAngle::operator+(const cSAngle& other) const {
    return cSAngle(static_cast<s16>(mAngle + other.mAngle));
}

/* 80253E14-80253E44       .text __mi__7cSAngleCFRC7cSAngle */
cSAngle cSAngle::operator-(const cSAngle& other) const {
    return cSAngle(static_cast<s16>(mAngle - other.mAngle));
}

/* 80253E44-80253E58       .text __apl__7cSAngleFRC7cSAngle */
void cSAngle::operator+=(const cSAngle& other) {
    mAngle += other.mAngle;
}

/* 80253E58-80253E6C       .text __ami__7cSAngleFRC7cSAngle */
void cSAngle::operator-=(const cSAngle& other) {
    mAngle -= other.mAngle;
}

/* 80253E6C-80253E98       .text __pl__7cSAngleCFs */
cSAngle cSAngle::operator+(s16 other) const {
    return cSAngle(static_cast<s16>(mAngle + other));
}

/* 80253E98-80253EC4       .text __mi__7cSAngleCFs */
cSAngle cSAngle::operator-(s16 other) const {
    return cSAngle(static_cast<s16>(mAngle - other));
}

/* 80253EC4-80253ED4       .text __apl__7cSAngleFs */
void cSAngle::operator+=(s16 other) {
    mAngle += other;
}

/* 80253ED4-80253EE4       .text __ami__7cSAngleFs */
void cSAngle::operator-=(s16 other) {
    mAngle -= other;
}

/* 80253EE4-80253F34       .text __ml__7cSAngleCFf */
cSAngle cSAngle::operator*(f32 f1) const {
    return cSAngle(static_cast<s16>(mAngle * f1));
}

/* 80253F34-80253F74       .text __amu__7cSAngleFf */
void cSAngle::operator*=(f32 f1) {
    mAngle *= f1;
}

/* 80253F74-80253FA0       .text __pl__FsRC7cSAngle */
cSAngle operator+(s16 other, const cSAngle& angle) {
    return cSAngle(static_cast<s16>(other + angle.Val()));
}

/* 80253FA0-80253FCC       .text __mi__FsRC7cSAngle */
cSAngle operator-(s16 other, const cSAngle& angle) {
    return cSAngle(static_cast<s16>(other - angle.Val()));
}

/* 80253FCC-80253FFC       .text __ct__7cDegreeFf */
cDegree::cDegree(f32 f) {
    Val(f);
}

/* 80253FFC-8025403C       .text Formal__7cDegreeFv */
cDegree& cDegree::Formal() {
    mDegree = cAngle::Adjust<f32>(mDegree, -180.0f, 180.0f);
    return *this;
}

/* 8025403C-80254060       .text Val__7cDegreeFf */
void cDegree::Val(f32 f) {
    mDegree = f;
    Formal();
}

/* 80254060-80254070       .text Radian__7cDegreeCFv */
f32 cDegree::Radian() const {
    return cAngle::Degree_to_Radian(mDegree);
}

/* 80254070-80254098       .text Sin__7cDegreeCFv */
f32 cDegree::Sin() const {
    return sin(Radian());
}

/* 80254098-802540C0       .text Cos__7cDegreeCFv */
f32 cDegree::Cos() const {
    return cos(Radian());
}

/* 802540C0-802540F0       .text __ct__7cSPolarFRC4cXyz */
cSPolar::cSPolar(const cXyz& xyz) {
    Val(xyz);
}

/* 802540F0-802541B0       .text Formal__7cSPolarFv */
cSPolar& cSPolar::Formal() {
    if (mRadial < 0.0f) {
        mRadial = -mRadial;
        cSAngle tmp(static_cast<s16>(-0x8000));
        mAngle1.Val(tmp - mAngle1);
        mAngle2.Val(mAngle2.Inv());
    }

    if (mAngle1.Val() < 0 && mAngle1.Val() != -0x8000) {
        mAngle1.Val(-mAngle1);
        mAngle2.Val(mAngle2.Inv());
    }

    return *this;
}

/* 802541B0-80254214       .text Val__7cSPolarFfss */
void cSPolar::Val(f32 f, s16 s1, s16 s2) {
    mRadial = f;
    mAngle1 = cSAngle(s1);
    mAngle2 = cSAngle(s2);
    Formal();
}

inline double square(f32 f) {
    return f * f;
}

/* 80254214-80254420       .text Val__7cSPolarFRC4cXyz */
void cSPolar::Val(const cXyz& xyz) {
    f32 x, y, z, tmp4;
    x = xyz.x;
    y = xyz.y;
    z = xyz.z;
    double tmp = square(z) + square(x);
    double tmp2 = square(y) + tmp;
    tmp4 = (tmp > 0.0) ? (f32)sqrt(tmp) : 0.0f;
    mRadial = (tmp2 > 0.0) ? (f32)sqrt(tmp2) : 0.0f;
    mAngle1.Val(cAngle::Radian_to_SAngle(cM_atan2f(tmp4, y)));
    mAngle2.Val(cAngle::Radian_to_SAngle(cM_atan2f(x, z)));
    Formal();
}

/* 80254420-802544E8       .text Xyz__7cSPolarCFv */
cXyz cSPolar::Xyz() const {
    f32 ang1Cos;
    f32 ang2Cos;
    f32 ang1Sin = mRadial * (f32)sin(mAngle1.Radian());
    ang2Cos = (f32)cos(mAngle2.Radian());
    ang1Cos = mRadial * (f32)cos(mAngle1.Radian());
    f32 ang2Sin = sin(mAngle2.Radian());
    return cXyz(ang1Sin * ang2Sin, ang1Cos, ang1Sin * ang2Cos);
}

/* 802544E8-80254524       .text Globe__7cSPolarCFP7cSGlobe */
void cSPolar::Globe(cSGlobe* globe) const {
    globe->Val(mRadial, 0x4000 - mAngle1.Val(), mAngle2.Val());
}

/* 80254524-80254554       .text __ct__7cSGlobeFRC7cSGlobe */
cSGlobe::cSGlobe(const cSGlobe& other) {
    Val(other);
}

/* 80254554-80254584       .text __ct__7cSGlobeFfss */
cSGlobe::cSGlobe(f32 f, s16 s1, s16 s2) {
    Val(f, s1, s2);
}

/* 80254584-802545B4       .text __ct__7cSGlobeFfRC7cSAngleRC7cSAngle */
cSGlobe::cSGlobe(f32 f, const cSAngle& a1, const cSAngle& a2) {
    Val(f, a1, a2);
}

/* 802545B4-802545E4       .text __ct__7cSGlobeFRC4cXyz */
cSGlobe::cSGlobe(const cXyz& xyz) {
    Val(xyz);
}

/* 802545E4-802546A0       .text Formal__7cSGlobeFv */
cSGlobe& cSGlobe::Formal() {
    if (mRadius < 0.0f) {
        mRadius = -mRadius;
        mAzimuth = -mAzimuth;
        mInclination.Val(mInclination.Inv());
    }

    if (mAzimuth.Val() < -0x4000 || 0x4000 < mAzimuth.Val()) {
        mAzimuth = cSAngle((s16)-0x8000) - mAzimuth;
        mInclination.Val(mInclination.Inv());
    }

    return *this;
}

/* 802546A0-802546D8       .text Val__7cSGlobeFRC7cSGlobe */
void cSGlobe::Val(const cSGlobe& other) {
    mRadius = other.mRadius;
    mAzimuth = other.mAzimuth;
    mInclination = other.mInclination;
    Formal();
}

/* 802546D8-8025473C       .text Val__7cSGlobeFfss */
void cSGlobe::Val(f32 f, s16 s1, s16 s2) {
    mRadius = f;
    mAzimuth = cSAngle(s1);
    mInclination = cSAngle(s2);
    Formal();
}

/* 8025473C-802547A4       .text Val__7cSGlobeFfRC7cSAngleRC7cSAngle */
void cSGlobe::Val(f32 f, const cSAngle& a1, const cSAngle& a2) {
    mRadius = f;
    mAzimuth = cSAngle(a1.Val());
    mInclination = cSAngle(a2.Val());
    Formal();
}

/* 802547A4-802547E8       .text Val__7cSGlobeFRC4cXyz */
void cSGlobe::Val(const cXyz& xyz) {
    cSPolar csp(xyz);
    csp.Globe(this);
    Formal();
}

/* 802547E8-80254828       .text Xyz__7cSGlobeCFv */
cXyz cSGlobe::Xyz() const {
    cSPolar csp;
    Polar(&csp);
    return csp.Xyz();
}

/* 80254828-80254864       .text Polar__7cSGlobeCFP7cSPolar */
void cSGlobe::Polar(cSPolar* csp) const {
    csp->Val(mRadius, 0x4000 - mAzimuth.Val(), mInclination.Val());
}

/* 80254864-80254890       .text Invert__7cSGlobeFv */
cSGlobe& cSGlobe::Invert() {
    mRadius = -mRadius;
    return Formal();
}
