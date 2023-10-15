#ifndef D_BG_D_BG_S_ROOF_CHK_H
#define D_BG_D_BG_S_ROOF_CHK_H

#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_bg_s_chk.h"

class dBgS_RoofChk : public cBgS_PolyInfo, public cBgS_Chk, public dBgS_Chk {
public:
    dBgS_RoofChk() {
        SetPolyPassChk(GetPolyPassChkInfo());
        SetGrpPassChk(GetGrpPassChkInfo());
        m_pos.x = 0.0f;
        m_pos.y = 0.0f;
        m_pos.z = 0.0f;
        SetActorPid(-1);
        field_0x44 = 0;
    }
    void Init();

    virtual ~dBgS_RoofChk() {}

    void SetPos(cXyz& pos) { m_pos = pos; }
    cXyz* GetPosP() { return &m_pos; }

private:
    /* 0x38 */ cXyz m_pos;
    /* 0x44 */ void* field_0x44;
    /* 0x48 */ void* field_0x48;
};  // Size: 0x4C

STATIC_ASSERT(sizeof(dBgS_RoofChk) == 0x4C);

class dBgS_LinkRoofChk : public dBgS_RoofChk {
public:
    dBgS_LinkRoofChk() { /* SetLink(); */ }
    virtual ~dBgS_LinkRoofChk();
};  // Size: 0x4C

#endif /* D_BG_D_BG_S_ROOF_CHK_H */