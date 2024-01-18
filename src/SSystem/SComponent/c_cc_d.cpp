//
// Generated by dtk
// Translation Unit: c_cc_d.cpp
//

#include "SSystem/SComponent/c_cc_d.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "f_pc/f_pc_manager.h"
#include "dolphin/types.h"

#define CHECK_FLOAT_CLASS(line, x) JUT_ASSERT(line, !(((sizeof(x) == sizeof(float)) ? __fpclassifyf((float)(x)) : __fpclassifyd((double)(x)) ) == 1));
#define CHECK_FLOAT_RANGE(line, x) JUT_ASSERT(line, -1.0e32f < x && x < 1.0e32f);
#define CHECK_VEC3_RANGE(line, v) JUT_ASSERT(line, -1.0e32f < v.x && v.x < 1.0e32f && -1.0e32f < v.y && v.y < 1.0e32f && -1.0e32f < v.z && v.z < 1.0e32f)

cXyz cCcD_ShapeAttr::m_virtual_center = cXyz::Zero;

/* 802413EC-80241428       .text Chk__15cCcD_DivideInfoCFRC15cCcD_DivideInfo */
bool cCcD_DivideInfo::Chk(const cCcD_DivideInfo& other) const {
    u32 mask = mRangeBits & other.mRangeBits;
    if ((mask & 0x7FF) == 0)
        return false;
    if ((mask & 0xFFE00000) == 0)
        return false;
    if ((mask & 0x1FF800) == 0)
        return false;
    return true;
}

/* 80241428-80241558       .text SetArea__15cCcD_DivideAreaFRC8cM3dGAab */
void cCcD_DivideArea::SetArea(const cM3dGAab& aabb) {
    *(cM3dGAab*)this = aabb;
    mScaledXDiff = (GetMaxX() - GetMinX()) * 0.09090909f;
    mXDiffIsZero = cM3d_IsZero(mScaledXDiff);
    if (!mXDiffIsZero)
        mInvScaledXDiff = 1.0f / mScaledXDiff;

    mScaledYDiff = (GetMaxY() - GetMinY()) * 0.1f;
    mYDiffIsZero = cM3d_IsZero(mScaledYDiff);
    if (!mYDiffIsZero)
        mInvScaledYDiff = 1.0f / mScaledYDiff;

    mScaledZDiff = (GetMaxZ() - GetMinZ()) * 0.09090909f;
    mZDiffIsZero = cM3d_IsZero(mScaledZDiff);
    if (!mZDiffIsZero)
        mInvScaledZDiff = 1.0f / mScaledZDiff;
}

/* 80241558-8024170C       .text CalcDivideInfo__15cCcD_DivideAreaFP15cCcD_DivideInfoRC8cM3dGAabUl */
void cCcD_DivideArea::CalcDivideInfo(cCcD_DivideInfo* pDivideInfo, const cM3dGAab& aab, u32 param_2) {
    if (param_2 != 0) {
        pDivideInfo->Set(0xFFFFFFFF);
    } else {
        u32 divInfo, yDivInfo, zDivInfo;
        if (!mXDiffIsZero) {
            s32 var1 = mInvScaledXDiff * (aab.mMin.x - mMin.x);
            s32 var3 = mInvScaledXDiff * (aab.mMax.x - mMin.x);
            if (10 < var3) {
                var3 = 10;
            }

            divInfo = (1 << (var3 + 1)) - 1;
            if (0 < var1) {
                var1--;
                divInfo &= ~((1 << var1) - 1);
            }
        } else {
            divInfo = 0x7FF;
        }

        if (!mYDiffIsZero) {
            s32 var1 = mInvScaledYDiff * (aab.mMin.y - mMin.y);
            s32 var3 = mInvScaledYDiff * (aab.mMax.y - mMin.y);
            if (9 < var3) {
                var3 = 9;
            }

            yDivInfo = (1 << (var3 + 1)) - 1;
            if (0 < var1) {
                var1--;
                yDivInfo &= ~((1 << var1) - 1);
            }
        } else {
            yDivInfo = 0x3FF;
        }
        divInfo |= yDivInfo << 11;

        if (!mZDiffIsZero) {
            s32 var1 = mInvScaledZDiff * (aab.mMin.z - mMin.z);
            s32 var3 = mInvScaledZDiff * (aab.mMax.z - mMin.z);
            if (10 < var3) {
                var3 = 10;
            }

            zDivInfo = (1 << (var3 + 1)) - 1;
            if (0 < var1) {
                var1--;
                zDivInfo &= ~((1 << var1) - 1);
            }
        } else {
            zDivInfo = 0x7FF;
        }
        divInfo |= zDivInfo << 21;

        pDivideInfo->Set(divInfo);
    }
}

/* 8024170C-80241924       .text CalcDivideInfoOverArea__15cCcD_DivideAreaFP15cCcD_DivideInfoRC8cM3dGAab */
void cCcD_DivideArea::CalcDivideInfoOverArea(cCcD_DivideInfo* pDivideInfo, const cM3dGAab& aab) {
    u32 divInfo, yDivInfo, zDivInfo;
    if (!mXDiffIsZero) {
        s32 var1 = mInvScaledXDiff * (aab.mMin.x - mMin.x);
        s32 var3 = mInvScaledXDiff * (aab.mMax.x - mMin.x);
        if ((var1 < 0 && var3 < 0) || (10 < var1 && var3 > 10)) {
            divInfo = 0;
        } else {
            if (10 < var3) {
                var3 = 10;
            }

            divInfo = (1 << (var3 + 1)) - 1;
            if (0 < var1) {
                var1--;
                divInfo &= ~((1 << var1) - 1);
            }
        }
    } else {
        divInfo = 0x7FF;
    }

    if (!mYDiffIsZero) {
        s32 var1 = mInvScaledYDiff * (aab.mMin.y - mMin.y);
        s32 var3 = mInvScaledYDiff * (aab.mMax.y - mMin.y);
        if ((var1 < 0 && var3 < 0) || (9 < var1 && var3 > 9)) {
            yDivInfo = 0;
        } else {
            if (9 < var3) {
                var3 = 9;
            }

            yDivInfo = (1 << (var3 + 1)) - 1;
            if (0 < var1) {
                var1--;
                yDivInfo &= ~((1 << var1) - 1);
            }
        }
    } else {
        yDivInfo = 0x3FF;
    }
    divInfo |= yDivInfo << 11;

    if (!mZDiffIsZero) {
        s32 var1 = mInvScaledZDiff * (aab.mMin.z - mMin.z);
        s32 var3 = mInvScaledZDiff * (aab.mMax.z - mMin.z);
        if ((var1 < 0 && var3 < 0) || (10 < var1 && var3 > 10)) {
            zDivInfo = 0;
        } else {
            if (10 < var3) {
                var3 = 10;
            }

            zDivInfo = (1 << (var3 + 1)) - 1;
            if (0 < var1) {
                var1--;
                zDivInfo &= ~((1 << var1) - 1);
            }
        }
    } else {
        zDivInfo = 0x7FF;
    }
    divInfo |= zDivInfo << 21;

    pDivideInfo->Set(divInfo);
}

/* 80241924-8024192C       .text GetGStts__9cCcD_SttsCFv */
const cCcD_GStts* cCcD_Stts::GetGStts() const {
    return NULL;
}

/* 8024192C-80241934       .text GetGStts__9cCcD_SttsFv */
cCcD_GStts* cCcD_Stts::GetGStts() {
    return NULL;
}

/* 80241934-80241994       .text Init__9cCcD_SttsFiiPvUi */
void cCcD_Stts::Init(int weight, int param_1, void* pProc, unsigned int procID) {
    Ct();
    mWeight = weight;
    field_0x15 = param_1;
    mActor = (fopAc_ac_c*)pProc;
    mApid = procID;
}

/* 80241994-802419C4       .text Ct__9cCcD_SttsFv */
void cCcD_Stts::Ct() {
    m_cc_move.x = 0.0f;
    m_cc_move.y = 0.0f;
    m_cc_move.z = 0.0f;
    mActor = NULL;
    mApid = fpcM_ERROR_PROCESS_ID_e;
    mWeight = 0;
    field_0x15 = 0;
    mDmg = 0;
}

/* 802419C4-80241C5C       .text PlusCcMove__9cCcD_SttsFfff */
void cCcD_Stts::PlusCcMove(f32 x, f32 y, f32 z) {
    m_cc_move.x += x;
    m_cc_move.y += y;
    m_cc_move.z += z;
    CHECK_FLOAT_CLASS(0x1bb, m_cc_move.x);
    CHECK_FLOAT_CLASS(0x1bc, m_cc_move.y);
    CHECK_FLOAT_CLASS(0x1bd, m_cc_move.z);
    CHECK_VEC3_RANGE(0x1c1, m_cc_move);
}

/* 80241C5C-80241C98       .text Set__8cCcD_ObjFRC11cCcD_SrcObj */
void cCcD_Obj::Set(const cCcD_SrcObj& src) {
    mFlags = src.mFlags;
    cCcD_ObjHitInf::Set(src.mSrcObjHitInf);
}

/* 80241C98-80241D68       .text CrossAtTg__12cCcD_TriAttrCFRC12cCcD_CpsAttrP4cXyz */
bool cCcD_TriAttr::CrossAtTg(const cCcD_CpsAttr& cps, cXyz* dst) const {
    if (Cross(cps, dst))
        return true;
    else
        return false;
}

/* 80241D68-80241DA0       .text CrossAtTg__12cCcD_TriAttrCFRC12cCcD_CylAttrP4cXyz */
bool cCcD_TriAttr::CrossAtTg(const cCcD_CylAttr& cyl, cXyz* dst) const {
    if (Cross(cyl, dst))
        return true;
    else
        return false;
}

/* 80241DA0-80241DDC       .text CrossAtTg__12cCcD_TriAttrCFRC12cCcD_SphAttrP4cXyz */
bool cCcD_TriAttr::CrossAtTg(const cCcD_SphAttr& sph, cXyz* dst) const {
    if (Cross(sph, dst))
        return true;
    else
        return false;
}

/* 80241DDC-80241E14       .text CrossAtTg__12cCcD_TriAttrCFRC12cCcD_TriAttrP4cXyz */
bool cCcD_TriAttr::CrossAtTg(const cCcD_TriAttr& tri, cXyz* dst) const {
    if (tri.Cross(*this, dst))
        return true;
    else
        return false;
}

/* 80241E14-80241EC4       .text CalcAabBox__12cCcD_TriAttrFv */
void cCcD_TriAttr::CalcAabBox() {
    mAab.ClearForMinMax();
    mAab.SetMinMax(mA);
    mAab.SetMinMax(mB);
    mAab.SetMinMax(mC);
}

/* 80241EC4-80241F60       .text GetNVec__12cCcD_TriAttrCFRC4cXyzP4cXyz */
bool cCcD_TriAttr::GetNVec(const cXyz& vec, cXyz* dst) const {
    f32 dot = mNormal.getDotProduct(vec);
    if (mD + dot >= 0.0f) {
        dst->set(mNormal);
    } else {
        dst->set(mNormal);
        *dst *= -1.0f;
    }
    return true;
}

/* 80241F60-80241FA4       .text CrossAtTg__12cCcD_CpsAttrCFRC12cCcD_CpsAttrP4cXyz */
bool cCcD_CpsAttr::CrossAtTg(const cCcD_CpsAttr& cps, cXyz* dst) const {
    if (Cross(&cps, dst))
        return true;
    else
        return false;
}

/* 80241FA4-80241FE8       .text CrossAtTg__12cCcD_CpsAttrCFRC12cCcD_CylAttrP4cXyz */
bool cCcD_CpsAttr::CrossAtTg(const cCcD_CylAttr& cyl, cXyz* dst) const {
    if (Cross(&cyl, dst))
        return true;
    else
        return false;
}

/* 80241FE8-8024202C       .text CrossAtTg__12cCcD_CpsAttrCFRC12cCcD_SphAttrP4cXyz */
bool cCcD_CpsAttr::CrossAtTg(const cCcD_SphAttr& sph, cXyz* dst) const {
    if (Cross(&sph, dst))
        return true;
    else
        return false;
}

/* 8024202C-802420FC       .text CrossAtTg__12cCcD_CpsAttrCFRC12cCcD_TriAttrP4cXyz */
bool cCcD_CpsAttr::CrossAtTg(const cCcD_TriAttr& tri, cXyz* dst) const {
    if (Cross(tri, dst))
        return true;
    else
        return false;
}

/* 802420FC-8024214C       .text CrossCo__12cCcD_CpsAttrCFRC12cCcD_CpsAttrPf */
bool cCcD_CpsAttr::CrossCo(const cCcD_CpsAttr& cps, f32* dst) const {
    *dst = 0.0f;
    cXyz xyz;
    if (Cross(&cps, &xyz)) 
        return true;
    else
        return false;
}

/* 8024214C-8024219C       .text CrossCo__12cCcD_CpsAttrCFRC12cCcD_CylAttrPf */
bool cCcD_CpsAttr::CrossCo(const cCcD_CylAttr& cyl, f32* dst) const {
    *dst = 0.0f;
    cXyz xyz;
    if (Cross(&cyl, &xyz)) 
        return true;
    else
        return false;
}

/* 8024219C-802421EC       .text CrossCo__12cCcD_CpsAttrCFRC12cCcD_SphAttrPf */
bool cCcD_CpsAttr::CrossCo(const cCcD_SphAttr& sph, f32* dst) const {
    *dst = 0.0f;
    cXyz xyz;
    if (Cross(&sph, &xyz)) 
        return true;
    else
        return false;
}

/* 802421EC-80242294       .text CalcAabBox__12cCcD_CpsAttrFv */
void cCcD_CpsAttr::CalcAabBox() {
    mAab.ClearForMinMax();
    mAab.SetMinMax(GetStart());
    mAab.SetMinMax(GetEnd());
    f32 r = mRadius;
    mAab.mMin.x -= r;
    mAab.mMin.y -= r;
    mAab.mMin.z -= r;
    mAab.mMax.x += r;
    mAab.mMax.y += r;
    mAab.mMax.z += r;
}

/* 80242294-802423FC       .text GetNVec__12cCcD_CpsAttrCFRC4cXyzP4cXyz */
bool cCcD_CpsAttr::GetNVec(const cXyz& vec, cXyz* dst) const {
    cXyz lin;
    CalcVec(&lin);
    f32 len = lin.getDotProduct(lin);
    if (cM3d_IsZero(len))
        return false;

    cXyz p0_v;
    VECSubtract(&vec, GetStartP(), &p0_v);
    f32 dot = p0_v.getDotProduct(lin) / len;

    cXyz pt;
    if (dot < 0.0f) {
        pt.set(*GetStartP());
    } else if (dot > 1.0f) {
        pt.set(*GetEndP());
    } else {
        VECScale(&lin, &lin, dot);
        VECAdd(&lin, GetStartP(), &pt);
    }

    VECSubtract(&vec, &pt, dst);
    if (cM3d_IsZero(VECMag(dst))) {
        dst->set(0.0f, 0.0f, 0.0f);
        return false;
    }

    VECNormalize(dst, dst);
    return true;
}

/* 802423FC-80242448       .text CrossAtTg__12cCcD_CylAttrCFRC12cCcD_CpsAttrP4cXyz */
bool cCcD_CylAttr::CrossAtTg(const cCcD_CpsAttr& cps, cXyz* dst) const {
    if (Cross(&cps, dst))
        return true;
    else
        return false;
}

/* 80242448-8024248C       .text CrossAtTg__12cCcD_CylAttrCFRC12cCcD_CylAttrP4cXyz */
bool cCcD_CylAttr::CrossAtTg(const cCcD_CylAttr& cyl, cXyz* dst) const {
    if (cross(&cyl, dst))
        return true;
    else
        return false;
}

/* 8024248C-802424D0       .text CrossAtTg__12cCcD_CylAttrCFRC12cCcD_SphAttrP4cXyz */
bool cCcD_CylAttr::CrossAtTg(const cCcD_SphAttr& sph, cXyz* dst) const {
    if (cross(&sph, dst))
        return true;
    else
        return false;
}

/* 802424D0-80242508       .text CrossAtTg__12cCcD_CylAttrCFRC12cCcD_TriAttrP4cXyz */
bool cCcD_CylAttr::CrossAtTg(const cCcD_TriAttr& tri, cXyz* dst) const {
    if (Cross(tri, dst))
        return true;
    else
        return false;
}

/* 80242508-8024254C       .text CrossCo__12cCcD_CylAttrCFRC12cCcD_CylAttrPf */
bool cCcD_CylAttr::CrossCo(const cCcD_CylAttr& cyl, f32* dst) const {
    if (cross(&cyl, dst)) 
        return true;
    else
        return false;
}

/* 8024254C-80242590       .text CrossCo__12cCcD_CylAttrCFRC12cCcD_SphAttrPf */
bool cCcD_CylAttr::CrossCo(const cCcD_SphAttr& sph, f32* dst) const {
    if (cross(&sph, dst)) 
        return true;
    else
        return false;
}

/* 80242590-802425E8       .text CrossCo__12cCcD_CylAttrCFRC12cCcD_CpsAttrPf */
bool cCcD_CylAttr::CrossCo(const cCcD_CpsAttr& cps, f32* dst) const {
    *dst = 0.0f;
    cXyz xyz;
    if (Cross(&cps, &xyz)) 
        return true;
    else
        return false;
}

/* 802425E8-8024264C       .text CalcAabBox__12cCcD_CylAttrFv */
void cCcD_CylAttr::CalcAabBox() {
    cXyz min, max;
    min.x = mCenter.x - mRadius;
    min.y = mCenter.y;
    min.z = mCenter.z - mRadius;
    max.x = mCenter.x + mRadius;
    max.y = mCenter.y + mHeight;
    max.z = mCenter.z + mRadius;
    mAab.mMin.set(min);
    mAab.mMax.set(max);
}

/* 8024264C-80242734       .text GetNVec__12cCcD_CylAttrCFRC4cXyzP4cXyz */
bool cCcD_CylAttr::GetNVec(const cXyz& param_0, cXyz* dst) const {
    cXyz xyz;
    if (mCenter.y > param_0.y) {
        xyz = mCenter;
    } else {
        if (mCenter.y + mHeight < param_0.y) {
            xyz = mCenter;
            xyz.y += mHeight;
        } else {
            xyz = mCenter;
            xyz.y = param_0.y;
        }
    }

    VECSubtract(&param_0, &xyz, dst);
    if (cM3d_IsZero(VECMag(dst))) {
        dst->set(0.0f, 0.0f, 0.0f);
        return false;
    } else {
        VECNormalize(dst, dst);
        return true;
    }
    return false;
}

/* 80242734-80242780       .text CrossAtTg__12cCcD_SphAttrCFRC12cCcD_CpsAttrP4cXyz */
bool cCcD_SphAttr::CrossAtTg(const cCcD_CpsAttr& cps, cXyz* dst) const {
    if (Cross(&cps, dst))
        return true;
    else
        return false;
}

/* 80242780-802427C4       .text CrossAtTg__12cCcD_SphAttrCFRC12cCcD_CylAttrP4cXyz */
bool cCcD_SphAttr::CrossAtTg(const cCcD_CylAttr& cyl, cXyz* dst) const {
    if (cross(&cyl, dst))
        return true;
    else
        return false;
}

/* 802427C4-80242808       .text CrossAtTg__12cCcD_SphAttrCFRC12cCcD_SphAttrP4cXyz */
bool cCcD_SphAttr::CrossAtTg(const cCcD_SphAttr& sph, cXyz* dst) const {
    if (cross(&sph, dst))
        return true;
    else
        return false;
}

/* 80242808-80242840       .text CrossAtTg__12cCcD_SphAttrCFRC12cCcD_TriAttrP4cXyz */
bool cCcD_SphAttr::CrossAtTg(const cCcD_TriAttr& tri, cXyz* dst) const {
    if (Cross(tri, dst))
        return true;
    else
        return false;
}

/* 80242840-80242894       .text CrossCo__12cCcD_SphAttrCFRC12cCcD_CylAttrPf */
bool cCcD_SphAttr::CrossCo(const cCcD_CylAttr& cyl, f32* dst) const {
    if (cross(&cyl, dst))
        return true;
    else
        return false;
}

/* 80242894-802428D8       .text CrossCo__12cCcD_SphAttrCFRC12cCcD_SphAttrPf */
bool cCcD_SphAttr::CrossCo(const cCcD_SphAttr& sph, f32* dst) const {
    if (cross(&sph, dst))
        return true;
    else
        return false;
}

/* 802428D8-80242930       .text CrossCo__12cCcD_SphAttrCFRC12cCcD_CpsAttrPf */
bool cCcD_SphAttr::CrossCo(const cCcD_CpsAttr& cps, f32* dst) const {
    cXyz xyz;
    *dst = 0.0f;
    if (Cross(&cps, &xyz))
        return true;
    else
        return false;
}

/* 80242930-802429B8       .text CalcAabBox__12cCcD_SphAttrFv */
void cCcD_SphAttr::CalcAabBox() {
    cXyz min, max;
    min = max = *GetCP();
    min.x -= GetR();
    min.y -= GetR();
    min.z -= GetR();
    max.x += GetR();
    max.y += GetR();
    max.z += GetR();
    GetWorkAab().Set(min, max);
}

/* 802429B8-80242A54       .text GetNVec__12cCcD_SphAttrCFRC4cXyzP4cXyz */
bool cCcD_SphAttr::GetNVec(const cXyz& vec, cXyz* dst) const {
    dst->x = vec.x - mCenter.x;
    dst->y = vec.y - mCenter.y;
    dst->z = vec.z - mCenter.z;

    if (cM3d_IsZero(VECMag(dst))) {
        dst->x = 0.0f;
        dst->y = 0.0f;
        dst->z = 0.0f;
        return false;
    } else {
        VECNormalize(dst, dst);
        return true;
    }
}
