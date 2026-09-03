/* ===== Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_04e71_06211_05fc3_08005_04eca_065e5_04e4b_065e5_0591a_070e6_05fe7_0064e_onCreate__Landroid_os_Bundle_2 @ 0012f780 ==== */
/* signature: undefined Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_04e71_06211_05fc3_08005_04eca_065e5_04e4b_065e5_0591a_070e6_05fe7_0064e_onCreate__Landroid_os_Bundle_2(void) */

void Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_04e71_06211_05fc3_08005_04eca_065e5_04e4b_065e5_0591a_070e6_05fe7_0064e_onCreate__Landroid_os_Bundle_2
               (long *param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  char cVar2;
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 uStack_50;
  undefined8 local_48;
  undefined8 local_40;
  long local_38;
  
  lVar1 = tpidr_el0;
  local_38 = *(long *)(lVar1 + 0x28);
  local_48 = 0;
  local_58 = 0;
  uStack_50 = 0;
  local_68 = 0;
  local_60 = 0;
  local_70 = 0;
  lVar3 = (**(code **)(*param_1 + 200))();
  uVar4 = (**(code **)(*param_1 + 200))(param_1,param_3);
  if (lVar3 == 0) {
    FUN_00126cfc(param_1,"java/lang/NullPointerException","NullPointerException");
  }
  else {
    uVar5 = FUN_001272e0(param_1,&local_48,&local_58,0,"androidx/appcompat/app/AppCompatActivity",
                         "onCreate","(Landroid/os/Bundle;)V");
    if ((uVar5 & 1) == 0) {
      local_40 = uVar4;
      (**(code **)(*param_1 + 0x2e8))(param_1,lVar3,local_48,local_58,&local_40);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if ((cVar2 == '\0') &&
         (uVar5 = FUN_001272e0(param_1,&uStack_50,&local_60,0,&DAT_0011ad01,"setContentView",
                               &DAT_00117730), (uVar5 & 1) == 0)) {
        local_40 = CONCAT44(local_40._4_4_,0x7f0b0037);
        (**(code **)(*param_1 + 0x1f8))(param_1,lVar3,local_60,&local_40);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 == '\0') &&
           (uVar5 = FUN_001272e0(param_1,&uStack_50,&local_68,0,&DAT_0011ad01,&DAT_0011a6bb,
                                 "(Landroid/os/Bundle;)V"), (uVar5 & 1) == 0)) {
          local_40 = uVar4;
          (**(code **)(*param_1 + 0x1f8))(param_1,lVar3,local_68,&local_40);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if ((cVar2 == '\0') &&
             (uVar5 = FUN_001272e0(param_1,&uStack_50,&local_70,0,&DAT_0011ad01,&DAT_0011ac0e,
                                   &DAT_00117ed6), (uVar5 & 1) == 0)) {
            (**(code **)(*param_1 + 0x1f8))(param_1,lVar3,local_70,&local_40);
            (**(code **)(*param_1 + 0x720))(param_1);
          }
        }
      }
    }
  }
  if (*(long *)(lVar1 + 0x28) == local_38) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}




