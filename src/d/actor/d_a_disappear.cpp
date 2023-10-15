//
// Generated by dtk
// Translation Unit: d_a_disappear.cpp
//

#include "JSystem/JKernel/JKRHeap.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "m_Do/m_Do_ext.h"
#include "dolphin/types.h"

class disappear_class : public fopAc_ac_c {
public:
    int m0000;
    int m0004;
    s32 mSwitchId;
    s16 mTimer;
};

/* 800E79C0-800E79C8       .text daDisappear_Draw__FP15disappear_class */
s32 daDisappear_Draw(disappear_class*) {
    return TRUE;
}

/* 800E79C8-800E7AC0       .text daDisappear_Execute__FP15disappear_class */
s32 daDisappear_Execute(disappear_class* i_this) {
    if (i_this->mTimer != 0) {
        i_this->mTimer--;
        
        if (i_this->mTimer == 0) {
            s8 health = i_this->mHealth;

            if (health != 1 && health != 3) {
                if (health == 2) {
                    fopAcM_createItemForBoss(i_this->getPositionP(), 0, i_this->getRoomNo(), &i_this->current.angle, NULL, 0);
                }
                else if (health >= 0x0A && health <= 0x0D) {
                    if (health < 0x0D) {
                        static u32 ki_item_d[] = {
                            0, 10, 16
                        };

                        fopAcM_createItem(i_this->getPositionP(), ki_item_d[health - 0xA], -1, -1, 0, NULL, 4, NULL);
                    }
                }
                else {
                    fopAcM_createIball(i_this->getPositionP(), i_this->mItemTableIdx, i_this->getRoomNo(), &i_this->current.angle, i_this->mSwitchId);
                }
            }
        }
    }
    else {
        fopAcM_delete(i_this);
    }

    return TRUE;
}

/* 800E7AC0-800E7AC8       .text daDisappear_IsDelete__FP15disappear_class */
s32 daDisappear_IsDelete(disappear_class*) {
    return TRUE;
}

/* 800E7AC8-800E7AD0       .text daDisappear_Delete__FP15disappear_class */
s32 daDisappear_Delete(disappear_class*) {
    return TRUE;
}

/* 800E7AD0-800E7DBC       .text set_disappear__FP15disappear_classf */
void set_disappear(disappear_class* i_this, float scale) {
    s8 rev = dComIfGp_getReverb(i_this->getRoomNo());
    mDoAud_seStart(JA_SE_CM_MONS_EXPLODE, &i_this->mEyePos, 0, rev);

    cXyz particleScale(scale, scale, scale);
    i_this->mTimer = g_regHIO.mChild[8].mShortRegs[0] + 0x3A;

    switch (i_this->mHealth) {
        case 0:
        case 2:
        case 10:
        case 0xB:
        case 0xC:
        case 0xD:
            dComIfGp_particle_set(0x14, &i_this->current.pos, 0, &particleScale);
        case 3:
            dComIfGp_particle_set(0x13, &i_this->current.pos, 0, &particleScale);
            dComIfGp_particle_setStripes(0x15, &i_this->current.pos, 0, &particleScale, 0xFF, 0x96);
            dComIfGp_particle_set(0x16, &i_this->current.pos, 0, &particleScale);
            break;
        case 1:
            dComIfGp_particle_set(0x13, &i_this->current.pos, 0, &particleScale);
            dComIfGp_particle_set(0x16, &i_this->current.pos, 0, &particleScale);
            break;
        case 4:
            dComIfGp_particle_set(0x043C, &i_this->current.pos);
            dComIfGp_particle_set(0x043D, &i_this->current.pos);
            dComIfGp_particle_set(0x043E, &i_this->current.pos);
            break;
    }
}

/* 800E7DBC-800E7E60       .text daDisappear_Create__FP10fopAc_ac_c */
s32 daDisappear_Create(fopAc_ac_c* i_this) {
    disappear_class* dis = static_cast<disappear_class*>(i_this);

    fopAcM_SetupActor(dis, disappear_class);

    u32 params = dis->mBase.mParameters;

    dis->mHealth = dis->mBase.mParameters & 0xFF;
    float scale = ((dis->mBase.mParameters >> 8) & 0xFF) * 0.1f;

    dis->mSwitchId = (dis->mBase.mParameters >> 0x10) & 0xFF;
    if (dis->mSwitchId == 0xFF) {
        dis->mSwitchId = -1;
    }

    set_disappear(dis, scale);
    return cPhs_COMPLEATE_e;
}

actor_method_class l_daDisappear_Method = {
    (process_method_func)daDisappear_Create,
    (process_method_func)daDisappear_Delete,
    (process_method_func)daDisappear_Execute,
    (process_method_func)daDisappear_IsDelete,
    (process_method_func)daDisappear_Draw,
};

actor_process_profile_definition g_profile_DISAPPEAR = {
    fpcLy_CURRENT_e,
    7,
    fpcLy_CURRENT_e,
    PROC_DISAPPEAR,
    &g_fpcLf_Method.mBase,
    sizeof(disappear_class),
    0,
    0,
    &g_fopAc_Method.base,
    0x0188,
    &l_daDisappear_Method,
    fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_0_e,
};
