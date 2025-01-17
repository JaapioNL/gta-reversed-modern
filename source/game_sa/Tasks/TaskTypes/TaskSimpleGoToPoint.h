#pragma once

#include "TaskSimpleGoTo.h"

class CTaskSimpleGoToPoint : public CTaskSimpleGoTo {
public:
    union {
        struct {
            uint8 m_bMoveTowardsTargetPoint : 1;
            uint8 m_b02 : 1;
            uint8 m_b03 : 1;
            uint8 m_b04 : 1;
            uint8 m_b05 : 1;
        } gotoPointFlags;
        uint8 m_GoToPointFlags;
    };
    CVector m_vecLastPedPos;

public:
    static constexpr auto Type = TASK_SIMPLE_GO_TO_POINT;

    CTaskSimpleGoToPoint(int32 moveState, const CVector& targetPoint, float fRadius, bool bMoveTowardsTargetPoint, bool a6);
    ~CTaskSimpleGoToPoint() override = default;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleGoToPoint(m_moveState, m_vecTargetPoint, m_fRadius, gotoPointFlags.m_bMoveTowardsTargetPoint, gotoPointFlags.m_b04); } // 0x66CC60
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

    // bDontCheckRadius is always false
    void UpdatePoint(const CVector& targetPosition, float fRadius, bool bDontCheckRadius);

    static void InjectHooks();
    CTaskSimpleGoToPoint* Constructor(int32 moveState, const CVector& targetPoint, float fRadius, bool bMoveTowardsTargetPoint, bool a6);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed_Reversed(CPed* ped);
};
VALIDATE_SIZE(CTaskSimpleGoToPoint, 0x30);
