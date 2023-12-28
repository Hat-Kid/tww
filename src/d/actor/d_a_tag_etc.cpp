//
// Generated by dtk
// Translation Unit: d_a_tag_etc.cpp
//

#include "d/actor/d_a_tag_etc.h"
#include "d/actor/d_a_npc_md.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "dolphin/types.h"

enum Action {
    ACT_WAIT,
    ACT_SEARCH,
    ACT_HUNT,
    ACT_READY,
    ACT_EVENT,
};

/* 00000078-00000084       .text getEventNo__11daTag_Etc_cFv */
u8 daTag_Etc_c::getEventNo() {
    return fopAcM_GetParam(this) >> 24;
}

/* 00000084-00000090       .text getType2__11daTag_Etc_cFv */
u8 daTag_Etc_c::getType2() {
    return fopAcM_GetParam(this) >> 8 & 0xF;
}

/* 00000090-000001B4       .text rangeCheck__11daTag_Etc_cFP10fopAc_ac_c */
BOOL daTag_Etc_c::rangeCheck(fopAc_ac_c* pActor) {
    float distanceMagnitude;
    cXyz delta;

    delta = pActor->current.pos - current.pos;
    if (delta.y < 0.0f)
        return FALSE;

    if (delta.absXZ() < (mScale.x * 100.0f) && delta.y <= (mScale.y * 100.0f))
        return TRUE;

    return FALSE;
}

/* 000001B4-00000214       .text otherCheck__11daTag_Etc_cFP10fopAc_ac_c */
BOOL daTag_Etc_c::otherCheck(fopAc_ac_c* pActor) {
    BOOL result;

    switch (getType2()) {
    case 0:
        if (pActor != NULL && ((daNpc_Md_c*)pActor)->checkStatusFly()) {
            result = TRUE;
        } else {
            result = FALSE;
        }
        break;
    default:
        result = TRUE;
        break;
    }
    return result;
}

/* 00000214-000002EC       .text demoProc__11daTag_Etc_cFv */
void daTag_Etc_c::demoProc() {
    daNpc_Md_c* pMedli;
    int staffIdx;
    u8 cVar3;
    pMedli = (daNpc_Md_c*)fopAcM_SearchByID(mProcID);
    staffIdx = dComIfGp_evmng_getMyStaffId("TAG_ETC_D", NULL, 0);

    if (staffIdx != -1) {
        cVar3 = getType2();
        switch (cVar3) {
        case 0:
            if (pMedli == NULL || (pMedli->m30F0 & 0x10) == 0) {
                if (field_0x29A > 0) {
                    field_0x29A--;
                } else {
                    dComIfGp_evmng_cutEnd(staffIdx);
                }
            }
            break;
        default:
            dComIfGp_evmng_cutEnd(staffIdx);
        }
    }
}

/* 000002EC-00000368       .text demoInitProc__11daTag_Etc_cFv */
void daTag_Etc_c::demoInitProc() {
    u8 cVar1;
    fopAc_ac_c* pActor;

    cVar1 = getType2();
    switch (cVar1) {
    case 0:
        pActor = fopAcM_SearchByID(mProcID);
        dComIfGp_event_setItemPartner(pActor);
        field_0x29A = 0xf;
        break;
    default:;
    }
    return;
}

/* 00000368-00000458       .text create__11daTag_Etc_cFv */
s32 daTag_Etc_c::create() {
    float fVar1;
    u8 stageEVNTListIndex;
    u16 uVar2;

    fopAcM_SetupActor(this, daTag_Etc_c);

    stageEVNTListIndex = getEventNo();
    mEventIdx = dComIfGp_evmng_getEventIdx(NULL, stageEVNTListIndex);
    if (mEventIdx == -1) {
        setActio(ACT_WAIT);
    } else {
        switch (getType2()) {
        case 0:
            setActio(ACT_SEARCH);
            break;
        default:
            setActio(ACT_WAIT);
            break;
        }
    }
    shape_angle.z = 0;
    shape_angle.x = 0;
    current.angle.z = 0;
    current.angle.x = 0;
    mAttentionInfo.mFlags = fopAc_Attn_ACTION_TALK_e;
    mAttentionInfo.mPosition.y += 150.0f;
    mEyePos.y += 150.0f;
    return cPhs_COMPLEATE_e;
}

/* 00000458-00000460       .text daTag_Etc_action_wait__FP11daTag_Etc_c */
static BOOL daTag_Etc_action_wait(daTag_Etc_c* i_this) {
    return TRUE;
}

/* 00000460-000004E8       .text daTag_Etc_action_search__FP11daTag_Etc_c */
static BOOL daTag_Etc_action_search(daTag_Etc_c* i_this) {
    fopAc_ac_c* actor = NULL;
    switch (i_this->getType2()) {
    case 0:
        actor = fopAcM_searchFromName("Md1", 0, 0);
        break;
    }

    if (actor != NULL) {
        i_this->mProcID = fopAcM_GetID(actor);
        i_this->setActio(ACT_HUNT);
    }

    return TRUE;
}

/* 000004E8-00000560       .text daTag_Etc_action_event__FP11daTag_Etc_c */
static BOOL daTag_Etc_action_event(daTag_Etc_c* i_this) {
    if (dComIfGp_evmng_endCheck(i_this->mEventIdx)) {
        i_this->mProcID = fpcM_ERROR_PROCESS_ID_e;
        i_this->setActio(ACT_SEARCH);
        dComIfGp_event_reset();
    } else {
        i_this->demoProc();
    }

    return TRUE;
}

/* 00000560-0000063C       .text daTag_Etc_action_ready__FP11daTag_Etc_c */
static BOOL daTag_Etc_action_ready(daTag_Etc_c* i_this) {
    fopAc_ac_c* actor = fopAcM_SearchByID(i_this->mProcID);
    if (i_this->mEvtInfo.checkCommandDemoAccrpt()) {
        i_this->demoInitProc();
        i_this->setActio(ACT_EVENT);
        daTag_Etc_action_event(i_this);
    } else if (actor == NULL || !i_this->rangeCheck(actor) || !i_this->otherCheck(actor)) {
        i_this->mProcID = fpcM_ERROR_PROCESS_ID_e;
        i_this->setActio(ACT_SEARCH);
    } else {
        fopAcM_orderOtherEventId(i_this, i_this->mEventIdx);
    }

    return TRUE;
}

/* 0000063C-000006EC       .text daTag_Etc_action_hunt__FP11daTag_Etc_c */
static BOOL daTag_Etc_action_hunt(daTag_Etc_c* i_this) {
    daNpc_Md_c* actor = (daNpc_Md_c*)fopAcM_SearchByID(i_this->mProcID);
    if (actor == NULL) {
        i_this->mProcID = fpcM_ERROR_PROCESS_ID_e;
        i_this->setActio(ACT_SEARCH);
        return TRUE;
    }

    if (i_this->rangeCheck(actor) && i_this->otherCheck(actor)) {
        actor->onBitCamTagIn();
    } else {
        actor->offBitCamTagIn();
    }

    return TRUE;
}

BOOL daTag_Etc_c::draw() {
    return TRUE;
}

BOOL daTag_Etc_c::execute() {
    static ActionFunc* l_action[] = {
        daTag_Etc_action_wait,
        daTag_Etc_action_search,
        daTag_Etc_action_hunt,
        daTag_Etc_action_ready,
        daTag_Etc_action_event,
    };
    l_action[mAction](this);
    return TRUE;
}

/* 000006EC-000006F4       .text daTag_Etc_Draw__FP11daTag_Etc_c */
static BOOL daTag_Etc_Draw(daTag_Etc_c* i_this) {
    return i_this->draw();
}

/* 000006F4-00000730       .text daTag_Etc_Execute__FP11daTag_Etc_c */
static BOOL daTag_Etc_Execute(daTag_Etc_c* i_this) {
    return i_this->execute();
}

/* 00000730-00000738       .text daTag_Etc_IsDelete__FP11daTag_Etc_c */
static BOOL daTag_Etc_IsDelete(daTag_Etc_c* i_this) {
    return TRUE;
}

/* 00000738-00000768       .text daTag_Etc_Delete__FP11daTag_Etc_c */
static BOOL daTag_Etc_Delete(daTag_Etc_c* i_this) {
    i_this->~daTag_Etc_c();
    return TRUE;
}

/* 00000768-00000788       .text daTag_Etc_Create__FP10fopAc_ac_c */
static s32 daTag_Etc_Create(fopAc_ac_c* i_this) {
    return reinterpret_cast<daTag_Etc_c*>(i_this)->create();
}

static actor_method_class l_daTag_Etc_Method = {
    (process_method_func)daTag_Etc_Create,
    (process_method_func)daTag_Etc_Delete,
    (process_method_func)daTag_Etc_Execute,
    (process_method_func)daTag_Etc_IsDelete,
    (process_method_func)daTag_Etc_Draw,
};

actor_process_profile_definition g_profile_TAG_ETC = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 7,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_TAG_ETC,
    /* Proc SubMtd  */ &g_fpcLf_Method.mBase,
    /* Size         */ sizeof(daTag_Etc_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0122,
    /* Actor SubMtd */ &l_daTag_Etc_Method,
    /* Status       */ fopAcStts_UNK40000_e | fopAcStts_UNK4000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_6_e,
};
