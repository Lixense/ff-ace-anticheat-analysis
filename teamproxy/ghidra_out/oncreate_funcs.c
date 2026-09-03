##### Java_com_Sx2_Team_Ban_h0k_initDcc__ #####
/* ===== Java_com_Sx2_Team_Ban_h0k_initDcc__ @ 001276b8 ==== */
/* signature: undefined Java_com_Sx2_Team_Ban_h0k_initDcc__(void) */

void Java_com_Sx2_Team_Ban_h0k_initDcc__(void)

{
  return;
}




##### Java_com_Sx2_Team_Ban_h0k__0003cinit_0003e__ #####
/* ===== Java_com_Sx2_Team_Ban_h0k__0003cinit_0003e__ @ 001276bc ==== */
/* signature: undefined Java_com_Sx2_Team_Ban_h0k__0003cinit_0003e__(void) */

void Java_com_Sx2_Team_Ban_h0k__0003cinit_0003e__(long *param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = (**(code **)(*param_1 + 200))();
  uVar2 = (**(code **)(*param_1 + 0x30))(param_1,"android/app/Application");
  uVar2 = (**(code **)(*param_1 + 0x108))(param_1,uVar2,"<init>",&DAT_00117ed6);
                    /* WARNING: Could not recover jumptable at 0x00127738. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x1f8))(param_1,uVar1,uVar2,0);
  return;
}




##### Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_04e71_06211_05fc3_08005_04eca_065e5_04e4b_065e5_0591a_070e6_05fe7_0064e_onCreate__Landroid_os_Bundle_2 #####
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




##### Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_0522b_0541b_053bb_0516e_04f55_065f6_08fd8_04e14_0653e_0767d_09e7f_09752_05d16_095f4_0064e_onCreate__Landroid_os_Bundle_2 #####
/* ===== Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_0522b_0541b_053bb_0516e_04f55_065f6_08fd8_04e14_0653e_0767d_09e7f_09752_05d16_095f4_0064e_onCreate__Landroid_os_Bundle_2 @ 00131198 ==== */
/* signature: undefined Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_0522b_0541b_053bb_0516e_04f55_065f6_08fd8_04e14_0653e_0767d_09e7f_09752_05d16_095f4_0064e_onCreate__Landroid_os_Bundle_2(void) */

/* WARNING: Type propagation algorithm not settling */

void Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_0522b_0541b_053bb_0516e_04f55_065f6_08fd8_04e14_0653e_0767d_09e7f_09752_05d16_095f4_0064e_onCreate__Landroid_os_Bundle_2
               (long *param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  int iVar12;
  long local_1e0;
  long local_1d8;
  undefined8 local_1d0;
  undefined8 local_1c8;
  undefined8 local_1c0;
  undefined8 local_1b8;
  undefined8 local_1b0;
  undefined8 local_1a8;
  undefined8 local_1a0;
  long local_198;
  long local_190;
  long local_188;
  long local_180;
  long local_178;
  long local_170;
  long local_168;
  long local_160;
  long local_158;
  long local_150;
  long local_148;
  long local_140;
  long local_138;
  long local_130;
  long local_128;
  long local_120;
  long local_118;
  long local_110;
  long local_108;
  undefined8 local_100;
  long local_f8;
  undefined8 local_f0;
  long local_e8;
  long local_e0;
  long local_d8 [10];
  long local_88;
  long lStack_80;
  ulong local_78;
  long local_70;
  
  lVar1 = tpidr_el0;
  local_70 = *(long *)(lVar1 + 0x28);
  local_d8[8] = 0;
  local_d8[9] = 0;
  local_d8[6] = 0;
  local_d8[7] = 0;
  local_d8[4] = 0;
  local_d8[5] = 0;
  local_d8[2] = 0;
  local_d8[3] = 0;
  local_d8[0] = 0;
  local_d8[1] = 0;
  local_e8 = 0;
  local_e0 = 0;
  local_f8 = 0;
  local_f0 = 0;
  local_108 = 0;
  local_100 = 0;
  local_118 = 0;
  local_110 = 0;
  local_128 = 0;
  local_120 = 0;
  local_138 = 0;
  local_130 = 0;
  local_148 = 0;
  local_140 = 0;
  local_158 = 0;
  local_150 = 0;
  local_168 = 0;
  local_160 = 0;
  local_178 = 0;
  local_170 = 0;
  local_188 = 0;
  local_180 = 0;
  local_198 = 0;
  local_190 = 0;
  local_1a8 = 0;
  local_1a0 = 0;
  local_1b8 = 0;
  local_1b0 = 0;
  local_1c8 = 0;
  local_1c0 = 0;
  local_1d8 = 0;
  local_1d0 = 0;
  lVar5 = (**(code **)(*param_1 + 200))();
  lVar6 = (**(code **)(*param_1 + 200))(param_1,param_3);
  if (lVar5 != 0) {
    uVar7 = FUN_001272e0(param_1,local_d8 + 9,&local_100,0,"android/app/Activity","onCreate",
                         "(Landroid/os/Bundle;)V");
    if ((uVar7 & 1) != 0) goto LAB_00132f0c;
    local_88 = lVar6;
    (**(code **)(*param_1 + 0x2e8))(param_1,lVar5,local_d8[9],local_100,&local_88);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if ((cVar2 != '\0') ||
       ((local_d8[8] == 0 &&
        (uVar7 = FUN_00127120(param_1,local_d8 + 8,"android/text/SpannableStringBuilder"),
        (uVar7 & 1) != 0)))) goto LAB_00132f0c;
    lVar6 = (**(code **)(*param_1 + 0xd8))(param_1,local_d8[8]);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_00132f0c;
    if (lVar6 != 0) {
      if ((local_108 == 0) &&
         (uVar7 = FUN_001272e0(param_1,local_d8 + 8,&local_108,0,
                               "android/text/SpannableStringBuilder","<init>",&DAT_00117ed6),
         (uVar7 & 1) != 0)) goto LAB_00132f0c;
      (**(code **)(*param_1 + 0x1f8))(param_1,lVar6,local_108,&local_88);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if ((cVar2 != '\0') ||
         ((local_110 == 0 &&
          (uVar7 = FUN_001272e0(param_1,local_d8 + 7,&local_110,0,&DAT_00119b87,"getIntent",
                                "()Landroid/content/Intent;"), (uVar7 & 1) != 0))))
      goto LAB_00132f0c;
      lVar8 = (**(code **)(*param_1 + 0x120))(param_1,lVar5,local_110,&local_88);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if ((cVar2 != '\0') ||
         ((lVar9 = (**(code **)(*param_1 + 0x538))(param_1,&DAT_0011ac2d), local_118 == 0 &&
          (uVar7 = FUN_001272e0(param_1,local_d8 + 6,&local_118,1,&DAT_00119a18,&DAT_0011ac0e,
                                "(Ljava/lang/String;)Ljava/lang/String;"), (uVar7 & 1) != 0))))
      goto LAB_00132f0c;
      local_88 = lVar9;
      lVar10 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[6],local_118,&local_88);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_00132f0c;
      if (lVar9 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
      }
      if (lVar8 == 0) {
        local_1e0 = 0;
      }
      else {
        if (lVar10 != 0) {
          (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
        }
        lVar9 = (**(code **)(*param_1 + 0x580))(param_1,0x10);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 != '\0') ||
           (((**(code **)(*param_1 + 0x680))(param_1,lVar9,0,0x10,&DAT_0011c15e), local_120 == 0 &&
            (uVar7 = FUN_001272e0(param_1,local_d8 + 5,&local_120,1,&DAT_0011567b,&DAT_0011a6bb,
                                  "([B)Ljava/lang/String;"), (uVar7 & 1) != 0)))) goto LAB_00132f0c;
        local_88 = lVar9;
        lVar10 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[5],local_120,&local_88);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar2 != '\0') goto LAB_00132f0c;
        if (lVar9 != 0) {
          (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
        }
        if ((local_118 == 0) &&
           (uVar7 = FUN_001272e0(param_1,local_d8 + 6,&local_118,1,&DAT_00119a18,&DAT_0011ac0e,
                                 "(Ljava/lang/String;)Ljava/lang/String;"), (uVar7 & 1) != 0))
        goto LAB_00132f0c;
        local_88 = lVar10;
        lVar9 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[6],local_118,&local_88);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar2 != '\0') goto LAB_00132f0c;
        if (lVar10 != 0) {
          (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
        }
        local_1e0 = (**(code **)(*param_1 + 0x580))(param_1,5);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 != '\0') ||
           (((**(code **)(*param_1 + 0x680))(param_1,local_1e0,0,5,&DAT_0011c16e), local_128 == 0 &&
            (uVar7 = FUN_001272e0(param_1,local_d8 + 4,&local_128,1,&DAT_00116867,&DAT_0011a6bb,
                                  "([BLjava/lang/String;Z)Ljava/lang/String;"), (uVar7 & 1) != 0))))
        goto LAB_00132f0c;
        local_78 = local_78 & 0xffffffffffffff00;
        local_88 = local_1e0;
        lStack_80 = lVar9;
        lVar11 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[4],local_128,&local_88);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar2 != '\0') goto LAB_00132f0c;
        if (lVar9 != 0) {
          (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
        }
        if ((local_130 == 0) &&
           (uVar7 = FUN_001272e0(param_1,local_d8 + 3,&local_130,0,"android/content/Intent",
                                 "getStringExtra","(Ljava/lang/String;)Ljava/lang/String;"),
           (uVar7 & 1) != 0)) goto LAB_00132f0c;
        local_88 = lVar11;
        lVar10 = (**(code **)(*param_1 + 0x120))(param_1,lVar8,local_130,&local_88);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar2 != '\0') goto LAB_00132f0c;
        if (lVar11 != 0) {
          (**(code **)(*param_1 + 0xb8))(param_1,lVar11);
        }
      }
      if (lVar10 != 0) {
        if ((local_138 == 0) &&
           (uVar7 = FUN_001272e0(param_1,local_d8 + 2,&local_138,0,"java/lang/String","isEmpty",
                                 &DAT_0011941d), (uVar7 & 1) != 0)) goto LAB_00132f0c;
        cVar2 = (**(code **)(*param_1 + 0x138))(param_1,lVar10,local_138,&local_88);
        cVar3 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar3 != '\0') goto LAB_00132f0c;
        if (cVar2 == '\0') {
          if (lVar8 != 0) {
            (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
          }
          lVar8 = (**(code **)(*param_1 + 0x580))(param_1,4);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if ((cVar2 != '\0') ||
             (((**(code **)(*param_1 + 0x680))(param_1,lVar8,0,4,&DAT_0011c173), local_120 == 0 &&
              (uVar7 = FUN_001272e0(param_1,local_d8 + 5,&local_120,1,&DAT_0011567b,&DAT_0011a6bb,
                                    "([B)Ljava/lang/String;"), (uVar7 & 1) != 0))))
          goto LAB_00132f0c;
          local_88 = lVar8;
          lVar9 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[5],local_120,&local_88);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar2 != '\0') goto LAB_00132f0c;
          if (lVar8 != 0) {
            (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
          }
          if ((local_118 == 0) &&
             (uVar7 = FUN_001272e0(param_1,local_d8 + 6,&local_118,1,&DAT_00119a18,&DAT_0011ac0e,
                                   "(Ljava/lang/String;)Ljava/lang/String;"), (uVar7 & 1) != 0))
          goto LAB_00132f0c;
          local_88 = lVar9;
          lVar8 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[6],local_118,&local_88);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar2 != '\0') goto LAB_00132f0c;
          if (lVar9 != 0) {
            (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
          }
          if ((local_140 == 0) &&
             (uVar7 = FUN_001272e0(param_1,local_d8 + 2,&local_140,0,"java/lang/String","split",
                                   "(Ljava/lang/String;)[Ljava/lang/String;"), (uVar7 & 1) != 0))
          goto LAB_00132f0c;
          local_88 = lVar8;
          lVar9 = (**(code **)(*param_1 + 0x120))(param_1,lVar10,local_140,&local_88);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar2 != '\0') goto LAB_00132f0c;
          if (lVar8 != 0) {
            (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
          }
          if (lVar9 != 0) {
            lVar8 = (**(code **)(*param_1 + 0x568))(param_1,lVar9,0);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_00132f0c;
            (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
            if (local_1e0 != 0) {
              (**(code **)(*param_1 + 0xb8))(param_1,local_1e0);
            }
            if ((local_f8 == 0) &&
               (uVar7 = FUN_001274cc(param_1,local_d8 + 7,&local_f8,1,&DAT_00119b87,&DAT_001156e1,
                                     "Ljava/util/Map;"), (uVar7 & 1) != 0)) goto LAB_00132f0c;
            local_1e0 = (**(code **)(*param_1 + 0x488))(param_1,local_d8[7],local_f8);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_00132f0c;
            if (local_1e0 != 0) {
              if ((local_148 == 0) &&
                 (uVar7 = FUN_001272e0(param_1,local_d8 + 1,&local_148,0,"java/util/Map",
                                       "containsKey","(Ljava/lang/Object;)Z"), (uVar7 & 1) != 0))
              goto LAB_00132f0c;
              local_88 = lVar8;
              cVar2 = (**(code **)(*param_1 + 0x138))(param_1,local_1e0,local_148,&local_88);
              cVar3 = (**(code **)(*param_1 + 0x720))(param_1);
              if (cVar3 != '\0') goto LAB_00132f0c;
              if (cVar2 == '\0') {
                if (lVar8 != 0) {
                  (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
                }
                lVar8 = (**(code **)(*param_1 + 0x538))(param_1,&DAT_0011ac2d);
                if ((local_118 == 0) &&
                   (uVar7 = FUN_001272e0(param_1,local_d8 + 6,&local_118,1,&DAT_00119a18,
                                         &DAT_0011ac0e,"(Ljava/lang/String;)Ljava/lang/String;"),
                   (uVar7 & 1) != 0)) goto LAB_00132f0c;
                local_88 = lVar8;
                lVar10 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[6],local_118,&local_88);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if (cVar2 != '\0') goto LAB_00132f0c;
                if (lVar8 != 0) {
                  (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
                }
              }
              else {
                (**(code **)(*param_1 + 0xb8))(param_1,local_1e0);
                if ((local_f8 == 0) &&
                   (uVar7 = FUN_001274cc(param_1,local_d8 + 7,&local_f8,1,&DAT_00119b87,
                                         &DAT_001156e1,"Ljava/util/Map;"), (uVar7 & 1) != 0))
                goto LAB_00132f0c;
                local_1e0 = (**(code **)(*param_1 + 0x488))(param_1,local_d8[7],local_f8);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if (cVar2 != '\0') goto LAB_00132f0c;
                if (local_1e0 == 0) goto LAB_00132ef4;
                if ((local_150 == 0) &&
                   (uVar7 = FUN_001272e0(param_1,local_d8 + 1,&local_150,0,"java/util/Map",
                                         &DAT_00115f2c,"(Ljava/lang/Object;)Ljava/lang/Object;"),
                   (uVar7 & 1) != 0)) goto LAB_00132f0c;
                local_88 = lVar8;
                lVar10 = (**(code **)(*param_1 + 0x120))(param_1,local_1e0,local_150,&local_88);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if (cVar2 != '\0') goto LAB_00132f0c;
                if (lVar8 != 0) {
                  (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
                }
                if ((((local_d8[2] == 0) &&
                     (uVar7 = FUN_00127120(param_1,local_d8 + 2,"java/lang/String"),
                     (uVar7 & 1) != 0)) ||
                    (uVar7 = FUN_0012708c(param_1,lVar10,local_d8[2],"java/lang/String"),
                    (uVar7 & 1) != 0)) ||
                   (cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0'))
                goto LAB_00132f0c;
              }
              if (lVar10 != 0) {
                if ((local_138 != 0) ||
                   (uVar7 = FUN_001272e0(param_1,local_d8 + 2,&local_138,0,"java/lang/String",
                                         "isEmpty",&DAT_0011941d), (uVar7 & 1) == 0)) {
                  cVar2 = (**(code **)(*param_1 + 0x138))(param_1,lVar10,local_138,&local_88);
                  cVar3 = (**(code **)(*param_1 + 0x720))(param_1);
                  if (cVar3 == '\0') {
                    if (cVar2 == '\0') {
                      if ((local_158 == 0) &&
                         (uVar7 = FUN_001272e0(param_1,local_d8 + 8,&local_158,0,
                                               "android/text/SpannableStringBuilder","append",
                                               "(Ljava/lang/CharSequence;)Landroid/text/SpannableStringBuilder;"
                                              ), (uVar7 & 1) != 0)) goto LAB_00132f0c;
                      local_88 = lVar10;
                      lVar8 = (**(code **)(*param_1 + 0x120))(param_1,lVar6,local_158,&local_88);
                      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                      if (cVar2 != '\0') goto LAB_00132f0c;
                      if (lVar8 != 0) {
                        (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
                      }
                    }
                    iVar4 = (**(code **)(*param_1 + 0x558))(param_1,lVar9);
                    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                    if (cVar2 == '\0') {
                      iVar12 = 1;
                      while( true ) {
                        if (iVar4 <= iVar12) goto LAB_00131b1c;
                        lVar8 = (**(code **)(*param_1 + 0x568))(param_1,lVar9,iVar12);
                        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                        if (cVar2 != '\0') break;
                        if (local_1e0 != 0) {
                          (**(code **)(*param_1 + 0xb8))(param_1,local_1e0);
                        }
                        if ((local_158 == 0) &&
                           (uVar7 = FUN_001272e0(param_1,local_d8 + 8,&local_158,0,
                                                 "android/text/SpannableStringBuilder","append",
                                                 "(Ljava/lang/CharSequence;)Landroid/text/SpannableStringBuilder;"
                                                ), (uVar7 & 1) != 0)) break;
                        local_88 = lVar8;
                        lVar11 = (**(code **)(*param_1 + 0x120))(param_1,lVar6,local_158,&local_88);
                        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                        if (cVar2 != '\0') break;
                        if (lVar11 != 0) {
                          (**(code **)(*param_1 + 0xb8))(param_1,lVar11);
                        }
                        if (lVar8 != 0) {
                          (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
                        }
                        lVar8 = (**(code **)(*param_1 + 0x580))(param_1,4);
                        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                        if ((cVar2 != '\0') ||
                           (((**(code **)(*param_1 + 0x680))(param_1,lVar8,0,4,&DAT_0011c18f),
                            local_120 == 0 &&
                            (uVar7 = FUN_001272e0(param_1,local_d8 + 5,&local_120,1,&DAT_0011567b,
                                                  &DAT_0011a6bb,"([B)Ljava/lang/String;"),
                            (uVar7 & 1) != 0)))) break;
                        local_88 = lVar8;
                        lVar11 = (**(code **)(*param_1 + 0x3a0))
                                           (param_1,local_d8[5],local_120,&local_88);
                        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                        if (cVar2 != '\0') break;
                        if (lVar8 != 0) {
                          (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
                        }
                        if ((local_118 == 0) &&
                           (uVar7 = FUN_001272e0(param_1,local_d8 + 6,&local_118,1,&DAT_00119a18,
                                                 &DAT_0011ac0e,
                                                 "(Ljava/lang/String;)Ljava/lang/String;"),
                           (uVar7 & 1) != 0)) break;
                        local_88 = lVar11;
                        local_1e0 = (**(code **)(*param_1 + 0x3a0))
                                              (param_1,local_d8[6],local_118,&local_88);
                        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                        if (cVar2 != '\0') break;
                        if (lVar11 != 0) {
                          (**(code **)(*param_1 + 0xb8))(param_1,lVar11);
                        }
                        if ((local_158 == 0) &&
                           (uVar7 = FUN_001272e0(param_1,local_d8 + 8,&local_158,0,
                                                 "android/text/SpannableStringBuilder","append",
                                                 "(Ljava/lang/CharSequence;)Landroid/text/SpannableStringBuilder;"
                                                ), (uVar7 & 1) != 0)) break;
                        local_88 = local_1e0;
                        lVar8 = (**(code **)(*param_1 + 0x120))(param_1,lVar6,local_158,&local_88);
                        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                        if (cVar2 != '\0') break;
                        if (lVar8 != 0) {
                          (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
                        }
                        iVar12 = iVar12 + 1;
                        iVar4 = (**(code **)(*param_1 + 0x558))(param_1,lVar9);
                        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                        if (cVar2 != '\0') break;
                      }
                    }
                  }
                }
                goto LAB_00132f0c;
              }
            }
          }
        }
        else {
          (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
          lVar9 = (**(code **)(*param_1 + 0x580))(param_1,0x10);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if ((cVar2 != '\0') ||
             (((**(code **)(*param_1 + 0x680))(param_1,lVar9,0,0x10,&DAT_0011c193), local_120 == 0
              && (uVar7 = FUN_001272e0(param_1,local_d8 + 5,&local_120,1,&DAT_0011567b,&DAT_0011a6bb
                                       ,"([B)Ljava/lang/String;"), (uVar7 & 1) != 0))))
          goto LAB_00132f0c;
          local_88 = lVar9;
          lVar10 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[5],local_120,&local_88);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar2 != '\0') goto LAB_00132f0c;
          if (lVar9 != 0) {
            (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
          }
          if ((local_118 == 0) &&
             (uVar7 = FUN_001272e0(param_1,local_d8 + 6,&local_118,1,&DAT_00119a18,&DAT_0011ac0e,
                                   "(Ljava/lang/String;)Ljava/lang/String;"), (uVar7 & 1) != 0))
          goto LAB_00132f0c;
          local_88 = lVar10;
          lVar11 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[6],local_118,&local_88);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar2 != '\0') goto LAB_00132f0c;
          if (lVar10 != 0) {
            (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
          }
          if (lVar8 != 0) {
            (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
          }
          lVar9 = (**(code **)(*param_1 + 0x580))(param_1,0x1b);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if ((cVar2 != '\0') ||
             (((**(code **)(*param_1 + 0x680))(param_1,lVar9,0,0x1b,&DAT_0011c1a3), local_1d8 == 0
              && (uVar7 = FUN_001272e0(param_1,local_d8 + 4,&local_1d8,1,&DAT_00116867,&DAT_0011a6bb
                                       ,"([BLjava/lang/String;I)Ljava/lang/String;"),
                 (uVar7 & 1) != 0)))) goto LAB_00132f0c;
          local_78 = CONCAT44(local_78._4_4_,0x7647);
          local_88 = lVar9;
          lStack_80 = lVar11;
          lVar10 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[4],local_1d8,&local_88);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar2 != '\0') goto LAB_00132f0c;
          if (lVar11 != 0) {
            (**(code **)(*param_1 + 0xb8))(param_1,lVar11);
          }
          if ((local_158 == 0) &&
             (uVar7 = FUN_001272e0(param_1,local_d8 + 8,&local_158,0,
                                   "android/text/SpannableStringBuilder","append",
                                   "(Ljava/lang/CharSequence;)Landroid/text/SpannableStringBuilder;"
                                  ), (uVar7 & 1) != 0)) goto LAB_00132f0c;
          local_88 = lVar10;
          lVar8 = (**(code **)(*param_1 + 0x120))(param_1,lVar6,local_158,&local_88);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar2 != '\0') goto LAB_00132f0c;
          if (lVar8 != 0) {
            (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
          }
LAB_00131b1c:
          if (lVar10 != 0) {
            (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
          }
          if ((local_d8[0] == 0) &&
             (uVar7 = FUN_00127120(param_1,local_d8,"java/lang/StringBuilder"), (uVar7 & 1) != 0))
          goto LAB_00132f0c;
          lVar8 = (**(code **)(*param_1 + 0xd8))(param_1,local_d8[0]);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar2 != '\0') goto LAB_00132f0c;
          if (lVar8 != 0) {
            if ((local_160 == 0) &&
               (uVar7 = FUN_001272e0(param_1,local_d8,&local_160,0,"java/lang/StringBuilder",
                                     "<init>",&DAT_00117ed6), (uVar7 & 1) != 0)) goto LAB_00132f0c;
            (**(code **)(*param_1 + 0x1f8))(param_1,lVar8,local_160,&local_88);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if ((cVar2 != '\0') ||
               ((local_168 == 0 &&
                (uVar7 = FUN_001272e0(param_1,local_d8 + 7,&local_168,0,&DAT_00119b87,"getTitle",
                                      "()Ljava/lang/CharSequence;"), (uVar7 & 1) != 0))))
            goto LAB_00132f0c;
            lVar10 = (**(code **)(*param_1 + 0x120))(param_1,lVar5,local_168,&local_88);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_00132f0c;
            if (lVar9 != 0) {
              (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
            }
            if ((local_170 == 0) &&
               (uVar7 = FUN_001272e0(param_1,local_d8,&local_170,0,"java/lang/StringBuilder",
                                     "append","(Ljava/lang/Object;)Ljava/lang/StringBuilder;"),
               (uVar7 & 1) != 0)) goto LAB_00132f0c;
            local_88 = lVar10;
            lVar9 = (**(code **)(*param_1 + 0x120))(param_1,lVar8,local_170,&local_88);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_00132f0c;
            (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
            if (lVar10 != 0) {
              (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
            }
            lVar8 = (**(code **)(*param_1 + 0x580))(param_1,0x10);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if ((cVar2 != '\0') ||
               (((**(code **)(*param_1 + 0x680))(param_1,lVar8,0,0x10,&DAT_0011c177), local_120 == 0
                && (uVar7 = FUN_001272e0(param_1,local_d8 + 5,&local_120,1,&DAT_0011567b,
                                         &DAT_0011a6bb,"([B)Ljava/lang/String;"), (uVar7 & 1) != 0))
               )) goto LAB_00132f0c;
            local_88 = lVar8;
            lVar10 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[5],local_120,&local_88);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_00132f0c;
            if (lVar8 != 0) {
              (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
            }
            if ((local_118 == 0) &&
               (uVar7 = FUN_001272e0(param_1,local_d8 + 6,&local_118,1,&DAT_00119a18,&DAT_0011ac0e,
                                     "(Ljava/lang/String;)Ljava/lang/String;"), (uVar7 & 1) != 0))
            goto LAB_00132f0c;
            local_88 = lVar10;
            lVar8 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[6],local_118,&local_88);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_00132f0c;
            if (lVar10 != 0) {
              (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
            }
            if (local_1e0 != 0) {
              (**(code **)(*param_1 + 0xb8))(param_1,local_1e0);
            }
            lVar10 = (**(code **)(*param_1 + 0x580))(param_1,8);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if ((cVar2 != '\0') ||
               (((**(code **)(*param_1 + 0x680))(param_1,lVar10,0,8,&DAT_0011c187), local_178 == 0
                && (uVar7 = FUN_001272e0(param_1,local_d8 + 4,&local_178,1,&DAT_00116867,
                                         &DAT_0011a6bb,"([BLjava/lang/String;J)Ljava/lang/String;"),
                   (uVar7 & 1) != 0)))) goto LAB_00132f0c;
            local_78 = 0x35fee09c;
            local_88 = lVar10;
            lStack_80 = lVar8;
            lVar10 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[4],local_178,&local_88);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_00132f0c;
            if (lVar8 != 0) {
              (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
            }
            if (lVar9 != 0) {
              if ((local_180 == 0) &&
                 (uVar7 = FUN_001272e0(param_1,local_d8,&local_180,0,"java/lang/StringBuilder",
                                       "append","(Ljava/lang/String;)Ljava/lang/StringBuilder;"),
                 (uVar7 & 1) != 0)) goto LAB_00132f0c;
              local_88 = lVar10;
              lVar8 = (**(code **)(*param_1 + 0x120))(param_1,lVar9,local_180,&local_88);
              cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
              if (cVar2 != '\0') goto LAB_00132f0c;
              (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
              if (lVar8 != 0) {
                if ((local_188 == 0) &&
                   (uVar7 = FUN_001272e0(param_1,local_d8,&local_188,0,"java/lang/StringBuilder",
                                         "toString","()Ljava/lang/String;"), (uVar7 & 1) != 0))
                goto LAB_00132f0c;
                lVar9 = (**(code **)(*param_1 + 0x120))(param_1,lVar8,local_188,&local_88);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if ((cVar2 != '\0') ||
                   (((**(code **)(*param_1 + 0xb8))(param_1,lVar8), local_190 == 0 &&
                    (uVar7 = FUN_001272e0(param_1,local_d8 + 7,&local_190,0,&DAT_00119b87,"setTitle"
                                          ,"(Ljava/lang/CharSequence;)V"), (uVar7 & 1) != 0))))
                goto LAB_00132f0c;
                local_88 = lVar9;
                (**(code **)(*param_1 + 0x1f8))(param_1,lVar5,local_190,&local_88);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if (cVar2 != '\0') goto LAB_00132f0c;
                if (lVar9 != 0) {
                  (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
                }
                if ((local_e0 == 0) &&
                   (uVar7 = FUN_00127120(param_1,&local_e0,"android/widget/TextView"),
                   (uVar7 & 1) != 0)) goto LAB_00132f0c;
                lVar8 = (**(code **)(*param_1 + 0xd8))(param_1,local_e0);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if (cVar2 != '\0') goto LAB_00132f0c;
                if (lVar8 != 0) {
                  if ((local_198 == 0) &&
                     (uVar7 = FUN_001272e0(param_1,&local_e0,&local_198,0,"android/widget/TextView",
                                           "<init>","(Landroid/content/Context;)V"),
                     (uVar7 & 1) != 0)) goto LAB_00132f0c;
                  local_88 = lVar5;
                  (**(code **)(*param_1 + 0x1f8))(param_1,lVar8,local_198,&local_88);
                  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                  if ((cVar2 != '\0') ||
                     (uVar7 = FUN_001272e0(param_1,&local_e0,&local_1a0,0,"android/widget/TextView",
                                           "setText","(Ljava/lang/CharSequence;)V"),
                     (uVar7 & 1) != 0)) goto LAB_00132f0c;
                  local_88 = lVar6;
                  (**(code **)(*param_1 + 0x1f8))(param_1,lVar8,local_1a0,&local_88);
                  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                  if ((cVar2 != '\0') ||
                     (uVar7 = FUN_001272e0(param_1,&local_e0,&local_1a8,0,"android/widget/TextView",
                                           "setTextIsSelectable",&DAT_00116c21), (uVar7 & 1) != 0))
                  goto LAB_00132f0c;
                  local_88 = CONCAT71(local_88._1_7_,1);
                  (**(code **)(*param_1 + 0x1f8))(param_1,lVar8,local_1a8,&local_88);
                  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                  if ((cVar2 != '\0') ||
                     ((local_e8 == 0 &&
                      (uVar7 = FUN_00127120(param_1,&local_e8,"android/widget/HorizontalScrollView")
                      , (uVar7 & 1) != 0)))) goto LAB_00132f0c;
                  lVar9 = (**(code **)(*param_1 + 0xd8))(param_1,local_e8);
                  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                  if (cVar2 != '\0') goto LAB_00132f0c;
                  if (lVar9 != 0) {
                    uVar7 = FUN_001272e0(param_1,&local_e8,&local_1b0,0,
                                         "android/widget/HorizontalScrollView","<init>",
                                         "(Landroid/content/Context;)V");
                    if ((uVar7 & 1) != 0) goto LAB_00132f0c;
                    local_88 = lVar5;
                    (**(code **)(*param_1 + 0x1f8))(param_1,lVar9,local_1b0,&local_88);
                    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                    if (cVar2 != '\0') goto LAB_00132f0c;
                    (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
                    uVar7 = FUN_00127120(param_1,&local_f0,"android/widget/ScrollView");
                    if ((uVar7 & 1) != 0) goto LAB_00132f0c;
                    lVar6 = (**(code **)(*param_1 + 0xd8))(param_1,local_f0);
                    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                    if (cVar2 != '\0') goto LAB_00132f0c;
                    if (lVar6 != 0) {
                      uVar7 = FUN_001272e0(param_1,&local_f0,&local_1b8,0,
                                           "android/widget/ScrollView","<init>",
                                           "(Landroid/content/Context;)V");
                      if ((uVar7 & 1) == 0) {
                        local_88 = lVar5;
                        (**(code **)(*param_1 + 0x1f8))(param_1,lVar6,local_1b8,&local_88);
                        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                        if ((cVar2 == '\0') &&
                           (uVar7 = FUN_001272e0(param_1,&local_e8,&local_1c0,0,
                                                 "android/widget/HorizontalScrollView","addView",
                                                 "(Landroid/view/View;)V"), (uVar7 & 1) == 0)) {
                          local_88 = lVar6;
                          (**(code **)(*param_1 + 0x1f8))(param_1,lVar9,local_1c0,&local_88);
                          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                          if ((cVar2 == '\0') &&
                             (uVar7 = FUN_001272e0(param_1,&local_f0,&local_1c8,0,
                                                   "android/widget/ScrollView","addView",
                                                   "(Landroid/view/View;)V"), (uVar7 & 1) == 0)) {
                            local_88 = lVar8;
                            (**(code **)(*param_1 + 0x1f8))(param_1,lVar6,local_1c8,&local_88);
                            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                            if ((cVar2 == '\0') &&
                               (uVar7 = FUN_001272e0(param_1,local_d8 + 7,&local_1d0,0,&DAT_00119b87
                                                     ,"setContentView","(Landroid/view/View;)V"),
                               (uVar7 & 1) == 0)) {
                              local_88 = lVar9;
                              (**(code **)(*param_1 + 0x1f8))(param_1,lVar5,local_1d0,&local_88);
                              (**(code **)(*param_1 + 0x720))(param_1);
                            }
                          }
                        }
                      }
                      goto LAB_00132f0c;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_00132ef4:
  FUN_00126cfc(param_1,"java/lang/NullPointerException","NullPointerException");
LAB_00132f0c:
  if (*(long *)(lVar1 + 0x28) != local_70) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}




##### Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_05343_078e8_04e07_051fb_08fd8_0575a_097e7_04efb_05c14_04e1c_0897f_05357_05317_098ce_0064e_onCreate__Landroid_os_Bundle_2 #####
/* ===== Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_05343_078e8_04e07_051fb_08fd8_0575a_097e7_04efb_05c14_04e1c_0897f_05357_05317_098ce_0064e_onCreate__Landroid_os_Bundle_2 @ 0013914c ==== */
/* signature: undefined Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_05343_078e8_04e07_051fb_08fd8_0575a_097e7_04efb_05c14_04e1c_0897f_05357_05317_098ce_0064e_onCreate__Landroid_os_Bundle_2(void) */

/* WARNING: Type propagation algorithm not settling */

void Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_05343_078e8_04e07_051fb_08fd8_0575a_097e7_04efb_05c14_04e1c_0897f_05357_05317_098ce_0064e_onCreate__Landroid_os_Bundle_2
               (long *param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  undefined8 uVar13;
  int iVar14;
  long local_238;
  long local_230;
  undefined8 local_228;
  undefined8 local_220;
  undefined8 local_218;
  undefined8 local_210;
  undefined8 local_208;
  long local_200;
  long local_1f8;
  long local_1f0;
  long local_1e8;
  undefined8 local_1e0;
  undefined8 local_1d8;
  undefined8 local_1d0;
  long local_1c8;
  long local_1c0;
  long local_1b8;
  long local_1b0;
  long local_1a8;
  long local_1a0;
  long local_198;
  long local_190;
  long local_188;
  long local_180;
  long local_178;
  undefined8 local_170;
  long local_168;
  long local_160;
  long local_158;
  long local_150;
  long local_148;
  long local_140;
  long local_138;
  long local_130;
  long local_128;
  long local_120;
  long local_118;
  long local_110;
  long local_108;
  undefined8 local_100;
  undefined8 local_f8;
  long local_f0;
  long local_e8;
  long local_e0 [11];
  long local_88;
  ulong local_80;
  undefined8 local_78;
  long local_70;
  
  lVar1 = tpidr_el0;
  local_70 = *(long *)(lVar1 + 0x28);
  local_e0[9] = 0;
  local_e0[10] = 0;
  local_e0[7] = 0;
  local_e0[8] = 0;
  local_e0[5] = 0;
  local_e0[6] = 0;
  local_e0[3] = 0;
  local_e0[4] = 0;
  local_e0[1] = 0;
  local_e0[2] = 0;
  local_e8 = 0;
  local_e0[0] = 0;
  local_f8 = 0;
  local_f0 = 0;
  local_108 = 0;
  local_100 = 0;
  local_118 = 0;
  local_110 = 0;
  local_128 = 0;
  local_120 = 0;
  local_138 = 0;
  local_130 = 0;
  local_148 = 0;
  local_140 = 0;
  local_158 = 0;
  local_150 = 0;
  local_168 = 0;
  local_160 = 0;
  local_178 = 0;
  local_170 = 0;
  local_188 = 0;
  local_180 = 0;
  local_198 = 0;
  local_190 = 0;
  local_1a8 = 0;
  local_1a0 = 0;
  local_1b8 = 0;
  local_1b0 = 0;
  local_1c8 = 0;
  local_1c0 = 0;
  local_1d8 = 0;
  local_1d0 = 0;
  local_1e8 = 0;
  local_1e0 = 0;
  local_1f8 = 0;
  local_1f0 = 0;
  local_208 = 0;
  local_200 = 0;
  local_218 = 0;
  local_210 = 0;
  local_228 = 0;
  local_220 = 0;
  local_238 = 0;
  local_230 = 0;
  lVar5 = (**(code **)(*param_1 + 200))();
  lVar6 = (**(code **)(*param_1 + 200))(param_1,param_3);
  if (lVar5 == 0) goto LAB_0013be9c;
  uVar7 = FUN_001272e0(param_1,local_e0 + 10,&local_170,0,"androidx/appcompat/app/AppCompatActivity"
                       ,"onCreate","(Landroid/os/Bundle;)V");
  if ((uVar7 & 1) != 0) goto LAB_0013beb4;
  local_88 = lVar6;
  (**(code **)(*param_1 + 0x2e8))(param_1,lVar5,local_e0[10],local_170,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_178 == 0 &&
      (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_178,0,&DAT_0011adbf,"setContentView",
                            &DAT_00117730), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  local_88 = CONCAT44(local_88._4_4_,0x7f0b001c);
  (**(code **)(*param_1 + 0x1f8))(param_1,lVar5,local_178,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_180 == 0 &&
      (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_180,0,&DAT_0011adbf,"findViewById",
                            "(I)Landroid/view/View;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  local_88 = CONCAT44(local_88._4_4_,0x7f0801fe);
  lVar6 = (**(code **)(*param_1 + 0x120))(param_1,lVar5,local_180,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (((cVar2 != '\0') ||
      ((((local_e0[8] == 0 &&
         (uVar7 = FUN_00127120(param_1,local_e0 + 8,"android/widget/Switch"), (uVar7 & 1) != 0)) ||
        (uVar7 = FUN_0012708c(param_1,lVar6,local_e0[8],"android/widget/Switch"), (uVar7 & 1) != 0))
       || (cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0')))) ||
     ((local_118 == 0 &&
      (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_118,0,&DAT_0011adbf,&DAT_0011a9ca,
                            "Landroid/widget/Switch;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  (**(code **)(*param_1 + 0x340))(param_1,lVar5,local_118,lVar6);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_180 == 0 &&
      (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_180,0,&DAT_0011adbf,"findViewById",
                            "(I)Landroid/view/View;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  local_88 = CONCAT44(local_88._4_4_,0x7f0801ff);
  lVar8 = (**(code **)(*param_1 + 0x120))(param_1,lVar5,local_180,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar6 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
  }
  if ((((local_e0[8] == 0) &&
       (uVar7 = FUN_00127120(param_1,local_e0 + 8,"android/widget/Switch"), (uVar7 & 1) != 0)) ||
      (uVar7 = FUN_0012708c(param_1,lVar8,local_e0[8],"android/widget/Switch"), (uVar7 & 1) != 0))
     || ((cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0' ||
         ((local_120 == 0 &&
          (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_120,0,&DAT_0011adbf,&DAT_0011a9e0,
                                "Landroid/widget/Switch;"), (uVar7 & 1) != 0))))))
  goto LAB_0013beb4;
  (**(code **)(*param_1 + 0x340))(param_1,lVar5,local_120,lVar8);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_180 == 0 &&
      (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_180,0,&DAT_0011adbf,"findViewById",
                            "(I)Landroid/view/View;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  local_88 = CONCAT44(local_88._4_4_,0x7f080200);
  lVar6 = (**(code **)(*param_1 + 0x120))(param_1,lVar5,local_180,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar8 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
  }
  if ((((local_e0[8] == 0) &&
       (uVar7 = FUN_00127120(param_1,local_e0 + 8,"android/widget/Switch"), (uVar7 & 1) != 0)) ||
      (uVar7 = FUN_0012708c(param_1,lVar6,local_e0[8],"android/widget/Switch"), (uVar7 & 1) != 0))
     || ((cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0' ||
         ((local_128 == 0 &&
          (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_128,0,&DAT_0011adbf,&DAT_0011b99d,
                                "Landroid/widget/Switch;"), (uVar7 & 1) != 0))))))
  goto LAB_0013beb4;
  (**(code **)(*param_1 + 0x340))(param_1,lVar5,local_128,lVar6);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_180 == 0 &&
      (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_180,0,&DAT_0011adbf,"findViewById",
                            "(I)Landroid/view/View;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  local_88 = CONCAT44(local_88._4_4_,0x7f080201);
  lVar8 = (**(code **)(*param_1 + 0x120))(param_1,lVar5,local_180,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar6 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
  }
  if (((((local_e0[8] == 0) &&
        (uVar7 = FUN_00127120(param_1,local_e0 + 8,"android/widget/Switch"), (uVar7 & 1) != 0)) ||
       (uVar7 = FUN_0012708c(param_1,lVar8,local_e0[8],"android/widget/Switch"), (uVar7 & 1) != 0))
      || (cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0')) ||
     ((local_130 == 0 &&
      (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_130,0,&DAT_0011adbf,&DAT_0011b33e,
                            "Landroid/widget/Switch;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  (**(code **)(*param_1 + 0x340))(param_1,lVar5,local_130,lVar8);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_180 == 0 &&
      (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_180,0,&DAT_0011adbf,"findViewById",
                            "(I)Landroid/view/View;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  local_88 = CONCAT44(local_88._4_4_,0x7f08006b);
  lVar6 = (**(code **)(*param_1 + 0x120))(param_1,lVar5,local_180,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar8 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
  }
  if ((((local_e0[7] == 0) &&
       (uVar7 = FUN_00127120(param_1,local_e0 + 7,"android/widget/Button"), (uVar7 & 1) != 0)) ||
      (uVar7 = FUN_0012708c(param_1,lVar6,local_e0[7],"android/widget/Button"), (uVar7 & 1) != 0))
     || ((cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0' ||
         ((local_138 == 0 &&
          (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_138,0,&DAT_0011adbf,&DAT_00117090,
                                "Landroid/widget/Button;"), (uVar7 & 1) != 0))))))
  goto LAB_0013beb4;
  (**(code **)(*param_1 + 0x340))(param_1,lVar5,local_138,lVar6);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_180 == 0 &&
      (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_180,0,&DAT_0011adbf,"findViewById",
                            "(I)Landroid/view/View;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  local_88 = CONCAT44(local_88._4_4_,0x7f08006c);
  lVar8 = (**(code **)(*param_1 + 0x120))(param_1,lVar5,local_180,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar6 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
  }
  if ((((local_e0[7] == 0) &&
       (uVar7 = FUN_00127120(param_1,local_e0 + 7,"android/widget/Button"), (uVar7 & 1) != 0)) ||
      (uVar7 = FUN_0012708c(param_1,lVar8,local_e0[7],"android/widget/Button"), (uVar7 & 1) != 0))
     || ((cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0' ||
         ((local_140 == 0 &&
          (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_140,0,&DAT_0011adbf,&DAT_0011b96f,
                                "Landroid/widget/Button;"), (uVar7 & 1) != 0))))))
  goto LAB_0013beb4;
  (**(code **)(*param_1 + 0x340))(param_1,lVar5,local_140,lVar8);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_180 == 0 &&
      (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_180,0,&DAT_0011adbf,"findViewById",
                            "(I)Landroid/view/View;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  local_88 = CONCAT44(local_88._4_4_,0x7f0801d4);
  lVar6 = (**(code **)(*param_1 + 0x120))(param_1,lVar5,local_180,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar8 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
  }
  if (((((local_e0[6] == 0) &&
        (uVar7 = FUN_00127120(param_1,local_e0 + 6,"android/widget/TextView"), (uVar7 & 1) != 0)) ||
       (uVar7 = FUN_0012708c(param_1,lVar6,local_e0[6],"android/widget/TextView"), (uVar7 & 1) != 0)
       ) || (cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0')) ||
     ((local_148 == 0 &&
      (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_148,0,&DAT_0011adbf,&DAT_0011a992,
                            "Landroid/widget/TextView;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  (**(code **)(*param_1 + 0x340))(param_1,lVar5,local_148,lVar6);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_180 == 0 &&
      (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_180,0,&DAT_0011adbf,"findViewById",
                            "(I)Landroid/view/View;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  local_88 = CONCAT44(local_88._4_4_,0x7f08025c);
  lVar8 = (**(code **)(*param_1 + 0x120))(param_1,lVar5,local_180,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar6 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
  }
  if ((((local_e0[6] == 0) &&
       (uVar7 = FUN_00127120(param_1,local_e0 + 6,"android/widget/TextView"), (uVar7 & 1) != 0)) ||
      (uVar7 = FUN_0012708c(param_1,lVar8,local_e0[6],"android/widget/TextView"), (uVar7 & 1) != 0))
     || ((cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0' ||
         ((local_150 == 0 &&
          (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_150,0,&DAT_0011adbf,&DAT_00116cfb,
                                "Landroid/widget/TextView;"), (uVar7 & 1) != 0))))))
  goto LAB_0013beb4;
  (**(code **)(*param_1 + 0x340))(param_1,lVar5,local_150,lVar8);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_180 == 0 &&
      (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_180,0,&DAT_0011adbf,"findViewById",
                            "(I)Landroid/view/View;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  local_88 = CONCAT44(local_88._4_4_,0x7f08006e);
  lVar6 = (**(code **)(*param_1 + 0x120))(param_1,lVar5,local_180,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar8 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
  }
  if ((((local_e0[7] == 0) &&
       (uVar7 = FUN_00127120(param_1,local_e0 + 7,"android/widget/Button"), (uVar7 & 1) != 0)) ||
      (uVar7 = FUN_0012708c(param_1,lVar6,local_e0[7],"android/widget/Button"), (uVar7 & 1) != 0))
     || ((cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0' ||
         ((local_158 == 0 &&
          (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_158,0,&DAT_0011adbf,&DAT_0011665c,
                                "Landroid/widget/Button;"), (uVar7 & 1) != 0))))))
  goto LAB_0013beb4;
  (**(code **)(*param_1 + 0x340))(param_1,lVar5,local_158,lVar6);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_180 == 0 &&
      (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_180,0,&DAT_0011adbf,"findViewById",
                            "(I)Landroid/view/View;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  local_88 = CONCAT44(local_88._4_4_,0x7f08006d);
  lVar8 = (**(code **)(*param_1 + 0x120))(param_1,lVar5,local_180,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar6 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
  }
  if (((((local_e0[7] == 0) &&
        (uVar7 = FUN_00127120(param_1,local_e0 + 7,"android/widget/Button"), (uVar7 & 1) != 0)) ||
       (uVar7 = FUN_0012708c(param_1,lVar8,local_e0[7],"android/widget/Button"), (uVar7 & 1) != 0))
      || (cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0')) ||
     ((local_160 == 0 &&
      (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_160,0,&DAT_0011adbf,&DAT_00119e13,
                            "Landroid/widget/Button;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  (**(code **)(*param_1 + 0x340))(param_1,lVar5,local_160,lVar8);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar8 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
  }
  if ((local_e0[8] == 0) &&
     (uVar7 = FUN_00127120(param_1,local_e0 + 8,"android/widget/Switch"), (uVar7 & 1) != 0))
  goto LAB_0013beb4;
  lVar6 = (**(code **)(*param_1 + 0x560))(param_1,4,local_e0[8],0);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_118 == 0 &&
      (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_118,0,&DAT_0011adbf,&DAT_0011a9ca,
                            "Landroid/widget/Switch;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  lVar8 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar5,local_118);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar6 == 0) goto LAB_0013be9c;
  (**(code **)(*param_1 + 0x570))(param_1,lVar6,0,lVar8);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_120 == 0 &&
      (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_120,0,&DAT_0011adbf,&DAT_0011a9e0,
                            "Landroid/widget/Switch;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  lVar9 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar5,local_120);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar8 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
  }
  (**(code **)(*param_1 + 0x570))(param_1,lVar6,1,lVar9);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_128 == 0 &&
      (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_128,0,&DAT_0011adbf,&DAT_0011b99d,
                            "Landroid/widget/Switch;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  lVar8 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar5,local_128);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  (**(code **)(*param_1 + 0x570))(param_1,lVar6,2,lVar8);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_130 == 0 &&
      (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_130,0,&DAT_0011adbf,&DAT_0011b33e,
                            "Landroid/widget/Switch;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  lVar10 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar5,local_130);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar8 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
  }
  (**(code **)(*param_1 + 0x570))(param_1,lVar6,3,lVar10);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_168 == 0 &&
      (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_168,0,&DAT_0011adbf,&DAT_00116344,
                            "[Landroid/widget/Switch;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  (**(code **)(*param_1 + 0x340))(param_1,lVar5,local_168,lVar6);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_188 == 0 &&
      (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_188,0,&DAT_0011adbf,"getIntent",
                            "()Landroid/content/Intent;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  lVar8 = (**(code **)(*param_1 + 0x120))(param_1,lVar5,local_188,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
  if (lVar9 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
  }
  lVar6 = (**(code **)(*param_1 + 0x580))(param_1,0x10);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     (((**(code **)(*param_1 + 0x680))(param_1,lVar6,0,0x10,&DAT_0011c4be), local_190 == 0 &&
      (uVar7 = FUN_001272e0(param_1,local_e0 + 5,&local_190,1,&DAT_0011567b,&DAT_0011a6bb,
                            "([B)Ljava/lang/String;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
  local_88 = lVar6;
  lVar9 = (**(code **)(*param_1 + 0x3a0))(param_1,local_e0[5],local_190,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar6 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
  }
  if ((local_198 == 0) &&
     (uVar7 = FUN_001272e0(param_1,local_e0 + 4,&local_198,1,&DAT_00119a18,&DAT_0011ac0e,
                           "(Ljava/lang/String;)Ljava/lang/String;"), (uVar7 & 1) != 0))
  goto LAB_0013beb4;
  local_88 = lVar9;
  uVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_e0[4],local_198,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (lVar9 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
  }
  if (lVar10 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
  }
  lVar6 = (**(code **)(*param_1 + 0x580))(param_1,8);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     (((**(code **)(*param_1 + 0x680))(param_1,lVar6,0,8,&DAT_0011c4ce), local_1a0 == 0 &&
      (uVar11 = FUN_001272e0(param_1,local_e0 + 3,&local_1a0,1,&DAT_00116867,&DAT_0011a6bb,
                             "([BLjava/lang/String;F)Ljava/lang/String;"), (uVar11 & 1) != 0))))
  goto LAB_0013beb4;
  local_78 = CONCAT44(local_78._4_4_,0x4ec797b2);
  local_88 = lVar6;
  local_80 = uVar7;
  lVar9 = (**(code **)(*param_1 + 0x3a0))(param_1,local_e0[3],local_1a0,&local_88);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_0013beb4;
  if (uVar7 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,uVar7);
  }
  if (lVar8 != 0) {
    if ((local_1a8 == 0) &&
       (uVar7 = FUN_001272e0(param_1,local_e0 + 2,&local_1a8,0,"android/content/Intent",
                             "getStringExtra","(Ljava/lang/String;)Ljava/lang/String;"),
       (uVar7 & 1) != 0)) goto LAB_0013beb4;
    local_88 = lVar9;
    lVar10 = (**(code **)(*param_1 + 0x120))(param_1,lVar8,local_1a8,&local_88);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_0013beb4;
    (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
    if (lVar10 == 0) {
LAB_0013a7c0:
      lVar8 = (**(code **)(*param_1 + 0x580))(param_1,0x10);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if ((cVar2 != '\0') ||
         (((**(code **)(*param_1 + 0x680))(param_1,lVar8,0,0x10,&DAT_0011c4d6), local_190 == 0 &&
          (uVar7 = FUN_001272e0(param_1,local_e0 + 5,&local_190,1,&DAT_0011567b,&DAT_0011a6bb,
                                "([B)Ljava/lang/String;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
      local_88 = lVar8;
      lVar10 = (**(code **)(*param_1 + 0x3a0))(param_1,local_e0[5],local_190,&local_88);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_0013beb4;
      if (lVar8 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
      }
      if ((local_198 == 0) &&
         (uVar7 = FUN_001272e0(param_1,local_e0 + 4,&local_198,1,&DAT_00119a18,&DAT_0011ac0e,
                               "(Ljava/lang/String;)Ljava/lang/String;"), (uVar7 & 1) != 0))
      goto LAB_0013beb4;
      local_88 = lVar10;
      uVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_e0[4],local_198,&local_88);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_0013beb4;
      if (lVar10 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
      }
      if (lVar9 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
      }
      lVar8 = (**(code **)(*param_1 + 0x580))(param_1,4);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if ((cVar2 != '\0') ||
         (((**(code **)(*param_1 + 0x680))(param_1,lVar8,0,4,&DAT_0011c4e6), local_1a0 == 0 &&
          (uVar11 = FUN_001272e0(param_1,local_e0 + 3,&local_1a0,1,&DAT_00116867,&DAT_0011a6bb,
                                 "([BLjava/lang/String;F)Ljava/lang/String;"), (uVar11 & 1) != 0))))
      goto LAB_0013beb4;
      local_78 = CONCAT44(local_78._4_4_,0x4ed86787);
      local_88 = lVar8;
      local_80 = uVar7;
      lVar9 = (**(code **)(*param_1 + 0x3a0))(param_1,local_e0[3],local_1a0,&local_88);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_0013beb4;
      if (uVar7 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,uVar7);
      }
      if ((local_1e8 == 0) &&
         (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_1e8,0,&DAT_0011adbf,
                               "getSharedPreferences",
                               "(Ljava/lang/String;I)Landroid/content/SharedPreferences;"),
         (uVar7 & 1) != 0)) goto LAB_0013beb4;
      local_80 = local_80 & 0xffffffff00000000;
      local_88 = lVar9;
      lVar12 = (**(code **)(*param_1 + 0x120))(param_1,lVar5,local_1e8,&local_88);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_0013beb4;
      if (lVar9 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
      }
      if (lVar8 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
      }
      lVar8 = (**(code **)(*param_1 + 0x580))(param_1,0x10);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if ((cVar2 != '\0') ||
         (((**(code **)(*param_1 + 0x680))(param_1,lVar8,0,0x10,&DAT_0011c4ea), local_190 == 0 &&
          (uVar7 = FUN_001272e0(param_1,local_e0 + 5,&local_190,1,&DAT_0011567b,&DAT_0011a6bb,
                                "([B)Ljava/lang/String;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
      local_88 = lVar8;
      lVar9 = (**(code **)(*param_1 + 0x3a0))(param_1,local_e0[5],local_190,&local_88);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_0013beb4;
      if (lVar8 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
      }
      if ((local_198 == 0) &&
         (uVar7 = FUN_001272e0(param_1,local_e0 + 4,&local_198,1,&DAT_00119a18,&DAT_0011ac0e,
                               "(Ljava/lang/String;)Ljava/lang/String;"), (uVar7 & 1) != 0))
      goto LAB_0013beb4;
      local_88 = lVar9;
      uVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_e0[4],local_198,&local_88);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_0013beb4;
      if (lVar9 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
      }
      if (lVar6 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
      }
      lVar6 = (**(code **)(*param_1 + 0x580))(param_1,8);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if ((cVar2 != '\0') ||
         (((**(code **)(*param_1 + 0x680))(param_1,lVar6,0,8,&DAT_0011c4fa), local_1f0 == 0 &&
          (uVar11 = FUN_001272e0(param_1,local_e0 + 3,&local_1f0,1,&DAT_00116867,&DAT_0011a6bb,
                                 "([BLjava/lang/String;D)Ljava/lang/String;"), (uVar11 & 1) != 0))))
      goto LAB_0013beb4;
      local_78 = 0x41bbb0f6de000000;
      local_88 = lVar6;
      local_80 = uVar7;
      lVar8 = (**(code **)(*param_1 + 0x3a0))(param_1,local_e0[3],local_1f0,&local_88);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_0013beb4;
      if (uVar7 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,uVar7);
      }
      if (lVar6 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
      }
      lVar6 = (**(code **)(*param_1 + 0x538))(param_1,&DAT_0011ac2d);
      if ((local_198 == 0) &&
         (uVar7 = FUN_001272e0(param_1,local_e0 + 4,&local_198,1,&DAT_00119a18,&DAT_0011ac0e,
                               "(Ljava/lang/String;)Ljava/lang/String;"), (uVar7 & 1) != 0))
      goto LAB_0013beb4;
      local_88 = lVar6;
      uVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_e0[4],local_198,&local_88);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_0013beb4;
      if (lVar6 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
      }
      if (lVar12 != 0) {
        if ((local_1f8 == 0) &&
           (uVar11 = FUN_001272e0(param_1,&local_f8,&local_1f8,0,"android/content/SharedPreferences"
                                  ,"getString",
                                  "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;"),
           (uVar11 & 1) != 0)) goto LAB_0013beb4;
        local_88 = lVar8;
        local_80 = uVar7;
        lVar10 = (**(code **)(*param_1 + 0x120))(param_1,lVar12,local_1f8,&local_88);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar2 != '\0') goto LAB_0013beb4;
        (**(code **)(*param_1 + 0xb8))(param_1,lVar12);
        if (lVar10 != 0) {
          if ((local_1b0 == 0) &&
             (uVar7 = FUN_001272e0(param_1,local_e0 + 1,&local_1b0,0,"java/lang/String","isEmpty",
                                   &DAT_0011941d), (uVar7 & 1) != 0)) goto LAB_0013beb4;
          cVar2 = (**(code **)(*param_1 + 0x138))(param_1,lVar10,local_1b0,&local_88);
          cVar3 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar3 != '\0') goto LAB_0013beb4;
          if (cVar2 == '\0') {
            if ((local_150 == 0) &&
               (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_150,0,&DAT_0011adbf,&DAT_00116cfb,
                                     "Landroid/widget/TextView;"), (uVar7 & 1) != 0))
            goto LAB_0013beb4;
            lVar6 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar5,local_150);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_0013beb4;
            if (lVar8 != 0) {
              (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
            }
            if (lVar6 != 0) goto LAB_0013b5f8;
          }
          else {
            (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
            lVar6 = (**(code **)(*param_1 + 0x580))(param_1,0x10);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if ((cVar2 != '\0') ||
               (((**(code **)(*param_1 + 0x680))(param_1,lVar6,0,0x10,&DAT_0011c502), local_190 == 0
                && (uVar7 = FUN_001272e0(param_1,local_e0 + 5,&local_190,1,&DAT_0011567b,
                                         &DAT_0011a6bb,"([B)Ljava/lang/String;"), (uVar7 & 1) != 0))
               )) goto LAB_0013beb4;
            local_88 = lVar6;
            lVar8 = (**(code **)(*param_1 + 0x3a0))(param_1,local_e0[5],local_190,&local_88);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_0013beb4;
            if (lVar6 != 0) {
              (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
            }
            if ((local_198 == 0) &&
               (uVar7 = FUN_001272e0(param_1,local_e0 + 4,&local_198,1,&DAT_00119a18,&DAT_0011ac0e,
                                     "(Ljava/lang/String;)Ljava/lang/String;"), (uVar7 & 1) != 0))
            goto LAB_0013beb4;
            local_88 = lVar8;
            uVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_e0[4],local_198,&local_88);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_0013beb4;
            if (lVar8 != 0) {
              (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
            }
            lVar6 = (**(code **)(*param_1 + 0x580))(param_1,0x30);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if ((cVar2 != '\0') ||
               (((**(code **)(*param_1 + 0x680))(param_1,lVar6,0,0x30,&DAT_0011c512), local_1f0 == 0
                && (uVar11 = FUN_001272e0(param_1,local_e0 + 3,&local_1f0,1,&DAT_00116867,
                                          &DAT_0011a6bb,"([BLjava/lang/String;D)Ljava/lang/String;")
                   , (uVar11 & 1) != 0)))) goto LAB_0013beb4;
            local_78 = 0x41b5de4192000000;
            local_88 = lVar6;
            local_80 = uVar7;
            uVar11 = (**(code **)(*param_1 + 0x3a0))(param_1,local_e0[3],local_1f0,&local_88);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_0013beb4;
            if (uVar7 != 0) {
              (**(code **)(*param_1 + 0xb8))(param_1,uVar7);
            }
            if ((local_200 == 0) &&
               (uVar7 = FUN_001272e0(param_1,&local_100,&local_200,1,"android/widget/Toast",
                                     "makeText",
                                     "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;"
                                    ), (uVar7 & 1) != 0)) goto LAB_0013beb4;
            local_78 = CONCAT44(local_78._4_4_,1);
            local_88 = lVar5;
            local_80 = uVar11;
            lVar8 = (**(code **)(*param_1 + 0x3a0))(param_1,local_100,local_200,&local_88);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_0013beb4;
            if (uVar11 != 0) {
              (**(code **)(*param_1 + 0xb8))(param_1,uVar11);
            }
            if (lVar8 != 0) {
              uVar7 = FUN_001272e0(param_1,&local_100,&local_208,0,"android/widget/Toast",
                                   &DAT_0011911a,&DAT_00117ed6);
              if ((uVar7 & 1) != 0) goto LAB_0013beb4;
              (**(code **)(*param_1 + 0x1f8))(param_1,lVar8,local_208,&local_88);
              cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
              if ((cVar2 != '\0') ||
                 (((**(code **)(*param_1 + 0xb8))(param_1,lVar8), local_e0[2] == 0 &&
                  (uVar7 = FUN_00127120(param_1,local_e0 + 2,"android/content/Intent"),
                  (uVar7 & 1) != 0)))) goto LAB_0013beb4;
              lVar8 = (**(code **)(*param_1 + 0xd8))(param_1,local_e0[2]);
              cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
              if (cVar2 != '\0') goto LAB_0013beb4;
              if (lVar6 != 0) {
                (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
              }
              if ((local_108 == 0) &&
                 (uVar7 = FUN_00127120(param_1,&local_108,&DAT_001179aa), (uVar7 & 1) != 0))
              goto LAB_0013beb4;
              uVar7 = (**(code **)(*param_1 + 200))(param_1,local_108);
              cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
              if (cVar2 != '\0') goto LAB_0013beb4;
              if (lVar8 != 0) {
                uVar11 = FUN_001272e0(param_1,local_e0 + 2,&local_210,0,"android/content/Intent",
                                      "<init>","(Landroid/content/Context;Ljava/lang/Class;)V");
                if ((uVar11 & 1) != 0) goto LAB_0013beb4;
                local_88 = lVar5;
                local_80 = uVar7;
                (**(code **)(*param_1 + 0x1f8))(param_1,lVar8,local_210,&local_88);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if ((cVar2 != '\0') ||
                   (uVar7 = FUN_001272e0(param_1,local_e0 + 2,&local_218,0,"android/content/Intent",
                                         "setFlags","(I)Landroid/content/Intent;"), (uVar7 & 1) != 0
                   )) goto LAB_0013beb4;
                local_88 = CONCAT44(local_88._4_4_,0x14000000);
                lVar6 = (**(code **)(*param_1 + 0x120))(param_1,lVar8,local_218,&local_88);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if (cVar2 != '\0') goto LAB_0013beb4;
                if (lVar6 != 0) {
                  (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
                }
                uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_220,0,&DAT_0011adbf,"startActivity"
                                     ,"(Landroid/content/Intent;)V");
                if ((uVar7 & 1) != 0) goto LAB_0013beb4;
                local_88 = lVar8;
                (**(code **)(*param_1 + 0x1f8))(param_1,lVar5,local_220,&local_88);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if ((cVar2 != '\0') ||
                   (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_228,0,&DAT_0011adbf,"finish",
                                         &DAT_00117ed6), (uVar7 & 1) != 0)) goto LAB_0013beb4;
                lVar6 = *param_1;
                uVar13 = local_228;
                goto LAB_0013be74;
              }
            }
          }
        }
      }
    }
    else {
      if ((local_1b0 == 0) &&
         (uVar7 = FUN_001272e0(param_1,local_e0 + 1,&local_1b0,0,"java/lang/String","isEmpty",
                               &DAT_0011941d), (uVar7 & 1) != 0)) goto LAB_0013beb4;
      cVar2 = (**(code **)(*param_1 + 0x138))(param_1,lVar10,local_1b0,&local_88);
      cVar3 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar3 != '\0') goto LAB_0013beb4;
      if (cVar2 != '\0') {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
        goto LAB_0013a7c0;
      }
      if ((local_150 == 0) &&
         (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_150,0,&DAT_0011adbf,&DAT_00116cfb,
                               "Landroid/widget/TextView;"), (uVar7 & 1) != 0)) goto LAB_0013beb4;
      lVar6 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar5,local_150);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_0013beb4;
      if (lVar9 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
      }
      if (lVar6 == 0) goto LAB_0013be9c;
LAB_0013b5f8:
      if ((local_1b8 == 0) &&
         (uVar7 = FUN_001272e0(param_1,local_e0 + 6,&local_1b8,0,"android/widget/TextView","setText"
                               ,"(Ljava/lang/CharSequence;)V"), (uVar7 & 1) != 0))
      goto LAB_0013beb4;
      local_88 = lVar10;
      (**(code **)(*param_1 + 0x1f8))(param_1,lVar6,local_1b8,&local_88);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if ((cVar2 != '\0') ||
         ((local_168 == 0 &&
          (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_168,0,&DAT_0011adbf,&DAT_00116344,
                                "[Landroid/widget/Switch;"), (uVar7 & 1) != 0)))) goto LAB_0013beb4;
      lVar8 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar5,local_168);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_0013beb4;
      (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
      if (lVar8 != 0) {
        iVar4 = (**(code **)(*param_1 + 0x558))(param_1,lVar8);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar2 != '\0') goto LAB_0013beb4;
        if (iVar4 < 1) {
          uVar7 = 0;
        }
        else {
          iVar14 = 0;
          lVar6 = 0;
          uVar11 = 0;
          do {
            uVar7 = (**(code **)(*param_1 + 0x568))(param_1,lVar8,iVar14);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_0013beb4;
            if (uVar11 != 0) {
              (**(code **)(*param_1 + 0xb8))(param_1,uVar11);
            }
            if (lVar6 != 0) {
              (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
            }
            if ((local_110 == 0) &&
               (uVar11 = FUN_00127120(param_1,&local_110,&DAT_00115050), (uVar11 & 1) != 0))
            goto LAB_0013beb4;
            lVar6 = (**(code **)(*param_1 + 0xd8))(param_1,local_110);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_0013beb4;
            if (lVar6 == 0) goto LAB_0013be9c;
            if ((local_230 == 0) &&
               (uVar11 = FUN_001272e0(param_1,&local_110,&local_230,0,&DAT_00115050,"<init>",
                                      &DAT_0011bc8e), (uVar11 & 1) != 0)) goto LAB_0013beb4;
            local_88 = lVar5;
            local_80 = uVar7;
            (**(code **)(*param_1 + 0x1f8))(param_1,lVar6,local_230,&local_88);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_0013beb4;
            if (uVar7 == 0) goto LAB_0013be9c;
            if ((local_238 == 0) &&
               (uVar11 = FUN_001272e0(param_1,local_e0 + 8,&local_238,0,"android/widget/Switch",
                                      "setOnCheckedChangeListener",
                                      "(Landroid/widget/CompoundButton$OnCheckedChangeListener;)V"),
               (uVar11 & 1) != 0)) goto LAB_0013beb4;
            local_88 = lVar6;
            (**(code **)(*param_1 + 0x1f8))(param_1,uVar7,local_238,&local_88);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_0013beb4;
            iVar14 = iVar14 + 1;
            uVar11 = uVar7;
          } while (iVar4 != iVar14);
        }
        if ((local_138 == 0) &&
           (uVar11 = FUN_001274cc(param_1,local_e0 + 9,&local_138,0,&DAT_0011adbf,&DAT_00117090,
                                  "Landroid/widget/Button;"), (uVar11 & 1) != 0)) goto LAB_0013beb4;
        lVar6 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar5,local_138);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar2 != '\0') goto LAB_0013beb4;
        (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
        if (uVar7 != 0) {
          (**(code **)(*param_1 + 0xb8))(param_1,uVar7);
        }
        if ((local_e0[0] == 0) &&
           (uVar7 = FUN_00127120(param_1,local_e0,&DAT_0011b558), (uVar7 & 1) != 0))
        goto LAB_0013beb4;
        lVar8 = (**(code **)(*param_1 + 0xd8))(param_1,local_e0[0]);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar2 != '\0') goto LAB_0013beb4;
        if (lVar8 != 0) {
          if ((local_1c0 == 0) &&
             (uVar7 = FUN_001272e0(param_1,local_e0,&local_1c0,0,&DAT_0011b558,"<init>",
                                   &DAT_00118b29), (uVar7 & 1) != 0)) goto LAB_0013beb4;
          local_88 = lVar5;
          (**(code **)(*param_1 + 0x1f8))(param_1,lVar8,local_1c0,&local_88);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar2 != '\0') goto LAB_0013beb4;
          if (lVar6 != 0) {
            if ((local_1c8 == 0) &&
               (uVar7 = FUN_001272e0(param_1,local_e0 + 7,&local_1c8,0,"android/widget/Button",
                                     "setOnClickListener","(Landroid/view/View$OnClickListener;)V"),
               (uVar7 & 1) != 0)) goto LAB_0013beb4;
            local_88 = lVar8;
            (**(code **)(*param_1 + 0x1f8))(param_1,lVar6,local_1c8,&local_88);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if ((cVar2 != '\0') ||
               ((local_158 == 0 &&
                (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_158,0,&DAT_0011adbf,&DAT_0011665c,
                                      "Landroid/widget/Button;"), (uVar7 & 1) != 0))))
            goto LAB_0013beb4;
            lVar9 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar5,local_158);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_0013beb4;
            (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
            (**(code **)(*param_1 + 0xb8))(param_1,lVar8);
            if ((local_e8 == 0) &&
               (uVar7 = FUN_00127120(param_1,&local_e8,&DAT_0011635a), (uVar7 & 1) != 0))
            goto LAB_0013beb4;
            lVar6 = (**(code **)(*param_1 + 0xd8))(param_1,local_e8);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_0013beb4;
            if (lVar6 != 0) {
              uVar7 = FUN_001272e0(param_1,&local_e8,&local_1d0,0,&DAT_0011635a,"<init>",
                                   &DAT_00118b29);
              if ((uVar7 & 1) != 0) goto LAB_0013beb4;
              local_88 = lVar5;
              (**(code **)(*param_1 + 0x1f8))(param_1,lVar6,local_1d0,&local_88);
              cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
              if (cVar2 != '\0') goto LAB_0013beb4;
              if (lVar9 != 0) {
                if ((local_1c8 == 0) &&
                   (uVar7 = FUN_001272e0(param_1,local_e0 + 7,&local_1c8,0,"android/widget/Button",
                                         "setOnClickListener",
                                         "(Landroid/view/View$OnClickListener;)V"), (uVar7 & 1) != 0
                   )) goto LAB_0013beb4;
                local_88 = lVar6;
                (**(code **)(*param_1 + 0x1f8))(param_1,lVar9,local_1c8,&local_88);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if ((cVar2 != '\0') ||
                   ((local_160 == 0 &&
                    (uVar7 = FUN_001274cc(param_1,local_e0 + 9,&local_160,0,&DAT_0011adbf,
                                          &DAT_00119e13,"Landroid/widget/Button;"), (uVar7 & 1) != 0
                    )))) goto LAB_0013beb4;
                lVar8 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar5,local_160);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if (cVar2 != '\0') goto LAB_0013beb4;
                (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
                (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
                if ((local_f0 == 0) &&
                   (uVar7 = FUN_00127120(param_1,&local_f0,&DAT_001159fd), (uVar7 & 1) != 0))
                goto LAB_0013beb4;
                lVar6 = (**(code **)(*param_1 + 0xd8))(param_1,local_f0);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if (cVar2 != '\0') goto LAB_0013beb4;
                if (lVar6 != 0) {
                  uVar7 = FUN_001272e0(param_1,&local_f0,&local_1d8,0,&DAT_001159fd,"<init>",
                                       &DAT_00118b29);
                  if ((uVar7 & 1) != 0) goto LAB_0013beb4;
                  local_88 = lVar5;
                  (**(code **)(*param_1 + 0x1f8))(param_1,lVar6,local_1d8,&local_88);
                  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                  if (cVar2 != '\0') goto LAB_0013beb4;
                  if (lVar8 != 0) {
                    if ((local_1c8 == 0) &&
                       (uVar7 = FUN_001272e0(param_1,local_e0 + 7,&local_1c8,0,
                                             "android/widget/Button","setOnClickListener",
                                             "(Landroid/view/View$OnClickListener;)V"),
                       (uVar7 & 1) != 0)) goto LAB_0013beb4;
                    local_88 = lVar6;
                    (**(code **)(*param_1 + 0x1f8))(param_1,lVar8,local_1c8,&local_88);
                    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                    if ((cVar2 != '\0') ||
                       (uVar7 = FUN_001272e0(param_1,local_e0 + 9,&local_1e0,0,&DAT_0011adbf,
                                             &DAT_0011b33e,&DAT_00117ed6), (uVar7 & 1) != 0))
                    goto LAB_0013beb4;
                    lVar6 = *param_1;
                    uVar13 = local_1e0;
LAB_0013be74:
                    (**(code **)(lVar6 + 0x1f8))(param_1,lVar5,uVar13,&local_88);
                    (**(code **)(*param_1 + 0x720))(param_1);
                    goto LAB_0013beb4;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_0013be9c:
  FUN_00126cfc(param_1,"java/lang/NullPointerException","NullPointerException");
LAB_0013beb4:
  if (*(long *)(lVar1 + 0x28) != local_70) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}




##### Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_05343_078e8_04e07_051fb_08fd8_0575a_097e7_04efb_05c14_04e1c_0897f_05357_05317_098ce_0064e_onResume__ #####
/* ===== Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_05343_078e8_04e07_051fb_08fd8_0575a_097e7_04efb_05c14_04e1c_0897f_05357_05317_098ce_0064e_onResume__ @ 0013bee8 ==== */
/* signature: undefined Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_05343_078e8_04e07_051fb_08fd8_0575a_097e7_04efb_05c14_04e1c_0897f_05357_05317_098ce_0064e_onResume__(void) */

void Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_05343_078e8_04e07_051fb_08fd8_0575a_097e7_04efb_05c14_04e1c_0897f_05357_05317_098ce_0064e_onResume__
               (long *param_1)

{
  long lVar1;
  char cVar2;
  char cVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  undefined8 local_128;
  undefined8 local_120;
  undefined8 local_118;
  undefined8 local_110;
  undefined8 local_108;
  long local_100;
  long local_f8;
  long local_f0;
  long local_e8;
  long local_e0;
  long local_d8;
  long local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined8 uStack_b0;
  undefined8 local_a8;
  undefined8 local_a0;
  undefined8 local_98;
  undefined8 local_90;
  undefined8 local_88;
  undefined8 local_80;
  long local_78;
  ulong local_70;
  undefined8 local_68;
  undefined1 local_60;
  long local_58;
  
  lVar1 = tpidr_el0;
  local_58 = *(long *)(lVar1 + 0x28);
  local_88 = 0;
  local_80 = 0;
  local_98 = 0;
  local_90 = 0;
  local_a8 = 0;
  local_a0 = 0;
  local_b8 = 0;
  uStack_b0 = 0;
  local_c8 = 0;
  local_c0 = 0;
  local_d8 = 0;
  local_d0 = 0;
  local_e8 = 0;
  local_e0 = 0;
  local_f8 = 0;
  local_f0 = 0;
  local_108 = 0;
  local_100 = 0;
  local_118 = 0;
  local_110 = 0;
  local_128 = 0;
  local_120 = 0;
  lVar4 = (**(code **)(*param_1 + 200))();
  if (lVar4 != 0) {
    uVar5 = FUN_001272e0(param_1,&local_80,&local_c8,0,"androidx/appcompat/app/AppCompatActivity",
                         "onResume",&DAT_00117ed6);
    if ((uVar5 & 1) != 0) goto LAB_0013c9d4;
    (**(code **)(*param_1 + 0x2e8))(param_1,lVar4,local_80,local_c8,&local_78);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if ((cVar2 != '\0') ||
       ((local_d0 == 0 &&
        (uVar5 = FUN_001272e0(param_1,&local_88,&local_d0,0,&DAT_0011adbf,&DAT_0011b33e,
                              &DAT_00117ed6), (uVar5 & 1) != 0)))) goto LAB_0013c9d4;
    (**(code **)(*param_1 + 0x1f8))(param_1,lVar4,local_d0,&local_78);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_0013c9d4;
    lVar6 = (**(code **)(*param_1 + 0x580))(param_1,0x10);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if ((cVar2 != '\0') ||
       (((**(code **)(*param_1 + 0x680))(param_1,lVar6,0,0x10,&DAT_0011c542), local_d8 == 0 &&
        (uVar5 = FUN_001272e0(param_1,&local_90,&local_d8,1,&DAT_0011567b,&DAT_0011a6bb,
                              "([B)Ljava/lang/String;"), (uVar5 & 1) != 0)))) goto LAB_0013c9d4;
    local_78 = lVar6;
    lVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_90,local_d8,&local_78);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_0013c9d4;
    if (lVar6 != 0) {
      (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
    }
    if ((local_e0 == 0) &&
       (uVar5 = FUN_001272e0(param_1,&local_98,&local_e0,1,&DAT_00119a18,&DAT_0011ac0e,
                             "(Ljava/lang/String;)Ljava/lang/String;"), (uVar5 & 1) != 0))
    goto LAB_0013c9d4;
    local_78 = lVar7;
    uVar5 = (**(code **)(*param_1 + 0x3a0))(param_1,local_98,local_e0,&local_78);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_0013c9d4;
    if (lVar7 != 0) {
      (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
    }
    lVar6 = (**(code **)(*param_1 + 0x580))(param_1,4);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if ((cVar2 != '\0') ||
       (((**(code **)(*param_1 + 0x680))(param_1,lVar6,0,4,&DAT_0011c552), local_e8 == 0 &&
        (uVar8 = FUN_001272e0(param_1,&local_a0,&local_e8,1,&DAT_00116867,&DAT_0011a6bb,
                              "([BLjava/lang/String;ZZ)Ljava/lang/String;"), (uVar8 & 1) != 0))))
    goto LAB_0013c9d4;
    local_68 = CONCAT71(local_68._1_7_,1);
    local_60 = 0;
    local_78 = lVar6;
    local_70 = uVar5;
    lVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_a0,local_e8,&local_78);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_0013c9d4;
    if (uVar5 != 0) {
      (**(code **)(*param_1 + 0xb8))(param_1,uVar5);
    }
    if ((local_f0 == 0) &&
       (uVar5 = FUN_001272e0(param_1,&local_88,&local_f0,0,&DAT_0011adbf,"getSharedPreferences",
                             "(Ljava/lang/String;I)Landroid/content/SharedPreferences;"),
       (uVar5 & 1) != 0)) goto LAB_0013c9d4;
    local_70 = local_70 & 0xffffffff00000000;
    local_78 = lVar7;
    lVar9 = (**(code **)(*param_1 + 0x120))(param_1,lVar4,local_f0,&local_78);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_0013c9d4;
    if (lVar7 != 0) {
      (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
    }
    if (lVar6 != 0) {
      (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
    }
    lVar6 = (**(code **)(*param_1 + 0x580))(param_1,0x10);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if ((cVar2 != '\0') ||
       (((**(code **)(*param_1 + 0x680))(param_1,lVar6,0,0x10,&DAT_0011c556), local_d8 == 0 &&
        (uVar5 = FUN_001272e0(param_1,&local_90,&local_d8,1,&DAT_0011567b,&DAT_0011a6bb,
                              "([B)Ljava/lang/String;"), (uVar5 & 1) != 0)))) goto LAB_0013c9d4;
    local_78 = lVar6;
    lVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_90,local_d8,&local_78);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_0013c9d4;
    if (lVar6 != 0) {
      (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
    }
    if ((local_e0 == 0) &&
       (uVar5 = FUN_001272e0(param_1,&local_98,&local_e0,1,&DAT_00119a18,&DAT_0011ac0e,
                             "(Ljava/lang/String;)Ljava/lang/String;"), (uVar5 & 1) != 0))
    goto LAB_0013c9d4;
    local_78 = lVar7;
    uVar5 = (**(code **)(*param_1 + 0x3a0))(param_1,local_98,local_e0,&local_78);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_0013c9d4;
    if (lVar7 != 0) {
      (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
    }
    lVar6 = (**(code **)(*param_1 + 0x580))(param_1,8);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if ((cVar2 != '\0') ||
       (((**(code **)(*param_1 + 0x680))(param_1,lVar6,0,8,&DAT_0011c566), local_f8 == 0 &&
        (uVar8 = FUN_001272e0(param_1,&local_a0,&local_f8,1,&DAT_00116867,&DAT_0011a6bb,
                              "([BLjava/lang/String;D)Ljava/lang/String;"), (uVar8 & 1) != 0))))
    goto LAB_0013c9d4;
    local_68 = 0xc1df75d1efc00000;
    local_78 = lVar6;
    local_70 = uVar5;
    lVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_a0,local_f8,&local_78);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_0013c9d4;
    if (uVar5 != 0) {
      (**(code **)(*param_1 + 0xb8))(param_1,uVar5);
    }
    if (lVar6 != 0) {
      (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
    }
    lVar6 = (**(code **)(*param_1 + 0x538))(param_1,&DAT_0011ac2d);
    if ((local_e0 == 0) &&
       (uVar5 = FUN_001272e0(param_1,&local_98,&local_e0,1,&DAT_00119a18,&DAT_0011ac0e,
                             "(Ljava/lang/String;)Ljava/lang/String;"), (uVar5 & 1) != 0))
    goto LAB_0013c9d4;
    local_78 = lVar6;
    uVar5 = (**(code **)(*param_1 + 0x3a0))(param_1,local_98,local_e0,&local_78);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_0013c9d4;
    if (lVar6 != 0) {
      (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
    }
    if (lVar9 != 0) {
      if ((local_100 == 0) &&
         (uVar8 = FUN_001272e0(param_1,&local_a8,&local_100,0,"android/content/SharedPreferences",
                               "getString",
                               "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;"),
         (uVar8 & 1) != 0)) goto LAB_0013c9d4;
      local_78 = lVar7;
      local_70 = uVar5;
      lVar6 = (**(code **)(*param_1 + 0x120))(param_1,lVar9,local_100,&local_78);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_0013c9d4;
      (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
      if (lVar6 != 0) {
        uVar5 = FUN_001272e0(param_1,&uStack_b0,&local_108,0,"java/lang/String","isEmpty",
                             &DAT_0011941d);
        if ((uVar5 & 1) != 0) goto LAB_0013c9d4;
        cVar2 = (**(code **)(*param_1 + 0x138))(param_1,lVar6,local_108,&local_78);
        cVar3 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar3 != '\0') || (cVar2 == '\0')) goto LAB_0013c9d4;
        (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
        uVar5 = FUN_00127120(param_1,&local_b8,"android/content/Intent");
        if ((uVar5 & 1) != 0) goto LAB_0013c9d4;
        lVar6 = (**(code **)(*param_1 + 0xd8))(param_1,local_b8);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar2 != '\0') goto LAB_0013c9d4;
        if (lVar7 != 0) {
          (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
        }
        uVar5 = FUN_00127120(param_1,&local_c0,&DAT_001179aa);
        if ((uVar5 & 1) != 0) goto LAB_0013c9d4;
        uVar5 = (**(code **)(*param_1 + 200))(param_1,local_c0);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar2 != '\0') goto LAB_0013c9d4;
        if (lVar6 != 0) {
          uVar8 = FUN_001272e0(param_1,&local_b8,&local_110,0,"android/content/Intent","<init>",
                               "(Landroid/content/Context;Ljava/lang/Class;)V");
          if ((uVar8 & 1) == 0) {
            local_78 = lVar4;
            local_70 = uVar5;
            (**(code **)(*param_1 + 0x1f8))(param_1,lVar6,local_110,&local_78);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if ((cVar2 == '\0') &&
               (uVar5 = FUN_001272e0(param_1,&local_b8,&local_118,0,"android/content/Intent",
                                     "setFlags","(I)Landroid/content/Intent;"), (uVar5 & 1) == 0)) {
              local_78 = CONCAT44(local_78._4_4_,0x14000000);
              lVar7 = (**(code **)(*param_1 + 0x120))(param_1,lVar6,local_118,&local_78);
              cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
              if (cVar2 == '\0') {
                if (lVar7 != 0) {
                  (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
                }
                uVar5 = FUN_001272e0(param_1,&local_88,&local_120,0,&DAT_0011adbf,"startActivity",
                                     "(Landroid/content/Intent;)V");
                if ((uVar5 & 1) == 0) {
                  local_78 = lVar6;
                  (**(code **)(*param_1 + 0x1f8))(param_1,lVar4,local_120,&local_78);
                  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                  if ((cVar2 == '\0') &&
                     (uVar5 = FUN_001272e0(param_1,&local_88,&local_128,0,&DAT_0011adbf,"finish",
                                           &DAT_00117ed6), (uVar5 & 1) == 0)) {
                    (**(code **)(*param_1 + 0x1f8))(param_1,lVar4,local_128,&local_78);
                    (**(code **)(*param_1 + 0x720))(param_1);
                  }
                }
              }
            }
          }
          goto LAB_0013c9d4;
        }
      }
    }
  }
  FUN_00126cfc(param_1,"java/lang/NullPointerException","NullPointerException");
LAB_0013c9d4:
  if (*(long *)(lVar1 + 0x28) != local_58) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}




##### Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_05c06_0519b_089d2_05f13_04e0d_05f97_063a7_090fd_062a4_094c1_08863_051b7_096be_07740_0064e_onCreate__ #####
/* ===== Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_05c06_0519b_089d2_05f13_04e0d_05f97_063a7_090fd_062a4_094c1_08863_051b7_096be_07740_0064e_onCreate__ @ 00140ff4 ==== */
/* signature: undefined Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_05c06_0519b_089d2_05f13_04e0d_05f97_063a7_090fd_062a4_094c1_08863_051b7_096be_07740_0064e_onCreate__(void) */

void Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_05c06_0519b_089d2_05f13_04e0d_05f97_063a7_090fd_062a4_094c1_08863_051b7_096be_07740_0064e_onCreate__
               (long *param_1)

{
  long lVar1;
  char cVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  undefined8 local_98;
  undefined8 local_90;
  undefined8 local_88;
  undefined8 local_80;
  undefined8 local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  long local_40;
  long local_38;
  
  lVar1 = tpidr_el0;
  local_38 = *(long *)(lVar1 + 0x28);
  local_50 = 0;
  local_48 = 0;
  local_60 = 0;
  local_58 = 0;
  local_70 = 0;
  local_68 = 0;
  local_80 = 0;
  local_78 = 0;
  local_90 = 0;
  local_88 = 0;
  local_98 = 0;
  lVar3 = (**(code **)(*param_1 + 200))();
  if (lVar3 != 0) {
    uVar4 = FUN_001272e0(param_1,&local_48,&local_78,0,&DAT_0011713c,"getApplicationContext",
                         "()Landroid/content/Context;");
    if ((uVar4 & 1) != 0) goto LAB_00141324;
    lVar5 = (**(code **)(*param_1 + 0x120))(param_1,lVar3,local_78,&local_40);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if ((cVar2 != '\0') ||
       (uVar4 = FUN_001274cc(param_1,&local_48,&local_70,1,&DAT_0011713c,&DAT_001156e1,
                             "Landroid/content/Context;"), (uVar4 & 1) != 0)) goto LAB_00141324;
    (**(code **)(*param_1 + 0x4d0))(param_1,local_48,local_70,lVar5);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_00141324;
    if (lVar5 != 0) {
      (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
    }
    uVar4 = FUN_00127120(param_1,&local_50,&DAT_00116acf);
    if ((uVar4 & 1) != 0) goto LAB_00141324;
    lVar5 = (**(code **)(*param_1 + 0xd8))(param_1,local_50);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_00141324;
    if (lVar5 != 0) {
      uVar4 = FUN_001272e0(param_1,&local_50,&local_80,0,&DAT_00116acf,"<init>",&DAT_00118610);
      if ((uVar4 & 1) == 0) {
        local_40 = lVar3;
        (**(code **)(*param_1 + 0x1f8))(param_1,lVar5,local_80,&local_40);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 == '\0') &&
           (uVar4 = FUN_001272e0(param_1,&local_58,&local_88,1,"java/lang/Thread",
                                 "setDefaultUncaughtExceptionHandler",
                                 "(Ljava/lang/Thread$UncaughtExceptionHandler;)V"), (uVar4 & 1) == 0
           )) {
          local_40 = lVar5;
          (**(code **)(*param_1 + 0x478))(param_1,local_58,local_88,&local_40);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if ((cVar2 == '\0') &&
             (uVar4 = FUN_001272e0(param_1,&local_60,&local_90,1,&DAT_0011b5d5,&DAT_00115791,
                                   &DAT_00117ed6), (uVar4 & 1) == 0)) {
            (**(code **)(*param_1 + 0x478))(param_1,local_60,local_90,&local_40);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if ((cVar2 == '\0') &&
               (uVar4 = FUN_001272e0(param_1,&local_68,&local_98,0,"android/app/Application",
                                     "onCreate",&DAT_00117ed6), (uVar4 & 1) == 0)) {
              (**(code **)(*param_1 + 0x2e8))(param_1,lVar3,local_68,local_98,&local_40);
              (**(code **)(*param_1 + 0x720))(param_1);
            }
          }
        }
      }
      goto LAB_00141324;
    }
  }
  FUN_00126cfc(param_1,"java/lang/NullPointerException","NullPointerException");
LAB_00141324:
  if (*(long *)(lVar1 + 0x28) == local_38) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}




##### Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_060df_089c9_065f6_04e4b_06795_05e2d_05931_05411_06765_04e4b_070df_0971e_0064e_onCreate__Landroid_os_Bundle_2 #####
/* ===== Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_060df_089c9_065f6_04e4b_06795_05e2d_05931_05411_06765_04e4b_070df_0971e_0064e_onCreate__Landroid_os_Bundle_2 @ 00146fbc ==== */
/* signature: undefined Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_060df_089c9_065f6_04e4b_06795_05e2d_05931_05411_06765_04e4b_070df_0971e_0064e_onCreate__Landroid_os_Bundle_2(void) */

/* WARNING: Type propagation algorithm not settling */

void Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_060df_089c9_065f6_04e4b_06795_05e2d_05931_05411_06765_04e4b_070df_0971e_0064e_onCreate__Landroid_os_Bundle_2
               (long *param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  char cVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  undefined8 local_180;
  undefined8 local_178;
  undefined8 local_170;
  undefined8 local_168;
  long local_160;
  long local_158;
  long local_150;
  long local_148;
  long local_140;
  long local_138;
  long local_130;
  long local_128;
  long local_120;
  long local_118;
  long local_110;
  long local_108;
  long local_100;
  long local_f8;
  long local_f0;
  long local_e8;
  undefined8 local_e0;
  long local_d8;
  long local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined8 local_b0;
  long local_a8;
  long local_a0 [6];
  ulong local_70;
  long lStack_68;
  undefined8 local_60;
  long local_58;
  
  lVar1 = tpidr_el0;
  local_58 = *(long *)(lVar1 + 0x28);
  local_a0[4] = 0;
  local_a0[5] = 0;
  local_a0[2] = 0;
  local_a0[3] = 0;
  local_a0[0] = 0;
  local_a0[1] = 0;
  local_b0 = 0;
  local_a8 = 0;
  local_c0 = 0;
  local_b8 = 0;
  local_d0 = 0;
  local_c8 = 0;
  local_e0 = 0;
  local_d8 = 0;
  local_f0 = 0;
  local_e8 = 0;
  local_100 = 0;
  local_f8 = 0;
  local_110 = 0;
  local_108 = 0;
  local_120 = 0;
  local_118 = 0;
  local_130 = 0;
  local_128 = 0;
  local_140 = 0;
  local_138 = 0;
  local_150 = 0;
  local_148 = 0;
  local_160 = 0;
  local_158 = 0;
  local_170 = 0;
  local_168 = 0;
  local_180 = 0;
  local_178 = 0;
  uVar3 = (**(code **)(*param_1 + 200))();
  uVar4 = (**(code **)(*param_1 + 200))(param_1,param_3);
  if (uVar3 != 0) {
    uVar5 = FUN_001272e0(param_1,local_a0 + 5,&local_e0,0,"android/app/Activity","onCreate",
                         "(Landroid/os/Bundle;)V");
    if ((uVar5 & 1) != 0) goto LAB_001480a4;
    local_70 = uVar4;
    (**(code **)(*param_1 + 0x2e8))(param_1,uVar3,local_a0[5],local_e0,&local_70);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if ((cVar2 != '\0') ||
       ((local_e8 == 0 &&
        (uVar4 = FUN_001272e0(param_1,local_a0 + 4,&local_e8,0,&DAT_0011b446,"setContentView",
                              &DAT_00117730), (uVar4 & 1) != 0)))) goto LAB_001480a4;
    local_70 = CONCAT44(local_70._4_4_,0x7f0b001d);
    (**(code **)(*param_1 + 0x1f8))(param_1,uVar3,local_e8,&local_70);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if ((cVar2 != '\0') ||
       ((local_f0 == 0 &&
        (uVar4 = FUN_001272e0(param_1,local_a0 + 4,&local_f0,0,&DAT_0011b446,"findViewById",
                              "(I)Landroid/view/View;"), (uVar4 & 1) != 0)))) goto LAB_001480a4;
    local_70 = CONCAT44(local_70._4_4_,0x7f080286);
    lVar6 = (**(code **)(*param_1 + 0x120))(param_1,uVar3,local_f0,&local_70);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (((cVar2 != '\0') ||
        ((((local_a0[3] == 0 &&
           (uVar4 = FUN_00127120(param_1,local_a0 + 3,"android/webkit/WebView"), (uVar4 & 1) != 0))
          || (uVar4 = FUN_0012708c(param_1,lVar6,local_a0[3],"android/webkit/WebView"),
             (uVar4 & 1) != 0)) || (cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0')
         ))) || ((local_d0 == 0 &&
                 (uVar4 = FUN_001274cc(param_1,local_a0 + 4,&local_d0,0,&DAT_0011b446,&DAT_0011a6bb,
                                       "Landroid/webkit/WebView;"), (uVar4 & 1) != 0))))
    goto LAB_001480a4;
    (**(code **)(*param_1 + 0x340))(param_1,uVar3,local_d0,lVar6);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if ((cVar2 != '\0') ||
       ((local_f0 == 0 &&
        (uVar4 = FUN_001272e0(param_1,local_a0 + 4,&local_f0,0,&DAT_0011b446,"findViewById",
                              "(I)Landroid/view/View;"), (uVar4 & 1) != 0)))) goto LAB_001480a4;
    local_70 = CONCAT44(local_70._4_4_,0x7f0801b6);
    lVar7 = (**(code **)(*param_1 + 0x120))(param_1,uVar3,local_f0,&local_70);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_001480a4;
    if (lVar6 != 0) {
      (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
    }
    if ((((local_a0[2] == 0) &&
         (uVar4 = FUN_00127120(param_1,local_a0 + 2,"android/widget/FrameLayout"), (uVar4 & 1) != 0)
         ) || (uVar4 = FUN_0012708c(param_1,lVar7,local_a0[2],"android/widget/FrameLayout"),
              (uVar4 & 1) != 0)) ||
       ((cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0' ||
        ((local_d8 == 0 &&
         (uVar4 = FUN_001274cc(param_1,local_a0 + 4,&local_d8,0,&DAT_0011b446,&DAT_001156e1,
                               "Landroid/widget/FrameLayout;"), (uVar4 & 1) != 0))))))
    goto LAB_001480a4;
    (**(code **)(*param_1 + 0x340))(param_1,uVar3,local_d8,lVar7);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if ((cVar2 != '\0') ||
       ((local_d0 == 0 &&
        (uVar4 = FUN_001274cc(param_1,local_a0 + 4,&local_d0,0,&DAT_0011b446,&DAT_0011a6bb,
                              "Landroid/webkit/WebView;"), (uVar4 & 1) != 0)))) goto LAB_001480a4;
    lVar6 = (**(code **)(*param_1 + 0x2f8))(param_1,uVar3,local_d0);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_001480a4;
    if (lVar7 != 0) {
      (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
    }
    if (lVar6 != 0) {
      if ((local_f8 == 0) &&
         (uVar4 = FUN_001272e0(param_1,local_a0 + 3,&local_f8,0,"android/webkit/WebView",
                               "getSettings","()Landroid/webkit/WebSettings;"), (uVar4 & 1) != 0))
      goto LAB_001480a4;
      lVar7 = (**(code **)(*param_1 + 0x120))(param_1,lVar6,local_f8,&local_70);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_001480a4;
      (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
      if (lVar7 != 0) {
        if ((local_100 == 0) &&
           (uVar4 = FUN_001272e0(param_1,local_a0 + 1,&local_100,0,"android/webkit/WebSettings",
                                 "setJavaScriptEnabled",&DAT_00116c21), (uVar4 & 1) != 0))
        goto LAB_001480a4;
        local_70 = CONCAT71(local_70._1_7_,1);
        (**(code **)(*param_1 + 0x1f8))(param_1,lVar7,local_100,&local_70);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 != '\0') ||
           ((local_108 == 0 &&
            (uVar4 = FUN_001272e0(param_1,local_a0 + 1,&local_108,0,"android/webkit/WebSettings",
                                  "setDomStorageEnabled",&DAT_00116c21), (uVar4 & 1) != 0))))
        goto LAB_001480a4;
        local_70 = CONCAT71(local_70._1_7_,1);
        (**(code **)(*param_1 + 0x1f8))(param_1,lVar7,local_108,&local_70);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 != '\0') ||
           ((local_110 == 0 &&
            (uVar4 = FUN_001272e0(param_1,local_a0 + 1,&local_110,0,"android/webkit/WebSettings",
                                  "setLoadWithOverviewMode",&DAT_00116c21), (uVar4 & 1) != 0))))
        goto LAB_001480a4;
        local_70 = CONCAT71(local_70._1_7_,1);
        (**(code **)(*param_1 + 0x1f8))(param_1,lVar7,local_110,&local_70);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 != '\0') ||
           ((local_118 == 0 &&
            (uVar4 = FUN_001272e0(param_1,local_a0 + 1,&local_118,0,"android/webkit/WebSettings",
                                  "setUseWideViewPort",&DAT_00116c21), (uVar4 & 1) != 0))))
        goto LAB_001480a4;
        local_70 = CONCAT71(local_70._1_7_,1);
        (**(code **)(*param_1 + 0x1f8))(param_1,lVar7,local_118,&local_70);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 != '\0') ||
           ((local_120 == 0 &&
            (uVar4 = FUN_001272e0(param_1,local_a0 + 1,&local_120,0,"android/webkit/WebSettings",
                                  "setSupportZoom",&DAT_00116c21), (uVar4 & 1) != 0))))
        goto LAB_001480a4;
        local_70 = CONCAT71(local_70._1_7_,1);
        (**(code **)(*param_1 + 0x1f8))(param_1,lVar7,local_120,&local_70);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 != '\0') ||
           ((local_128 == 0 &&
            (uVar4 = FUN_001272e0(param_1,local_a0 + 1,&local_128,0,"android/webkit/WebSettings",
                                  "setBuiltInZoomControls",&DAT_00116c21), (uVar4 & 1) != 0))))
        goto LAB_001480a4;
        local_70 = CONCAT71(local_70._1_7_,1);
        (**(code **)(*param_1 + 0x1f8))(param_1,lVar7,local_128,&local_70);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 != '\0') ||
           ((local_130 == 0 &&
            (uVar4 = FUN_001272e0(param_1,local_a0 + 1,&local_130,0,"android/webkit/WebSettings",
                                  "setDisplayZoomControls",&DAT_00116c21), (uVar4 & 1) != 0))))
        goto LAB_001480a4;
        local_70 = local_70 & 0xffffffffffffff00;
        (**(code **)(*param_1 + 0x1f8))(param_1,lVar7,local_130,&local_70);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 != '\0') ||
           ((local_d0 == 0 &&
            (uVar4 = FUN_001274cc(param_1,local_a0 + 4,&local_d0,0,&DAT_0011b446,&DAT_0011a6bb,
                                  "Landroid/webkit/WebView;"), (uVar4 & 1) != 0))))
        goto LAB_001480a4;
        lVar6 = (**(code **)(*param_1 + 0x2f8))(param_1,uVar3,local_d0);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 != '\0') ||
           (((**(code **)(*param_1 + 0xb8))(param_1,lVar7), local_a0[0] == 0 &&
            (uVar4 = FUN_00127120(param_1,local_a0,"android/webkit/WebChromeClient"),
            (uVar4 & 1) != 0)))) goto LAB_001480a4;
        uVar4 = (**(code **)(*param_1 + 0xd8))(param_1,local_a0[0]);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar2 != '\0') goto LAB_001480a4;
        if (uVar4 != 0) {
          if ((local_138 == 0) &&
             (uVar5 = FUN_001272e0(param_1,local_a0,&local_138,0,"android/webkit/WebChromeClient",
                                   "<init>",&DAT_00117ed6), (uVar5 & 1) != 0)) goto LAB_001480a4;
          (**(code **)(*param_1 + 0x1f8))(param_1,uVar4,local_138,&local_70);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar2 != '\0') goto LAB_001480a4;
          if (lVar6 != 0) {
            if ((local_140 == 0) &&
               (uVar5 = FUN_001272e0(param_1,local_a0 + 3,&local_140,0,"android/webkit/WebView",
                                     "setWebChromeClient","(Landroid/webkit/WebChromeClient;)V"),
               (uVar5 & 1) != 0)) goto LAB_001480a4;
            local_70 = uVar4;
            (**(code **)(*param_1 + 0x1f8))(param_1,lVar6,local_140,&local_70);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if ((cVar2 != '\0') ||
               ((local_d0 == 0 &&
                (uVar5 = FUN_001274cc(param_1,local_a0 + 4,&local_d0,0,&DAT_0011b446,&DAT_0011a6bb,
                                      "Landroid/webkit/WebView;"), (uVar5 & 1) != 0))))
            goto LAB_001480a4;
            lVar7 = (**(code **)(*param_1 + 0x2f8))(param_1,uVar3,local_d0);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_001480a4;
            (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
            (**(code **)(*param_1 + 0xb8))(param_1,uVar4);
            if ((local_a8 == 0) &&
               (uVar4 = FUN_00127120(param_1,&local_a8,
                                     "com/Sx2/Team/Ban/ActivityYoutubePlayerActivity$1"),
               (uVar4 & 1) != 0)) goto LAB_001480a4;
            uVar4 = (**(code **)(*param_1 + 0xd8))(param_1,local_a8);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_001480a4;
            if (uVar4 != 0) {
              if ((local_148 == 0) &&
                 (uVar5 = FUN_001272e0(param_1,&local_a8,&local_148,0,
                                       "com/Sx2/Team/Ban/ActivityYoutubePlayerActivity$1","<init>",
                                       &DAT_0011aa1b), (uVar5 & 1) != 0)) goto LAB_001480a4;
              local_70 = uVar3;
              (**(code **)(*param_1 + 0x1f8))(param_1,uVar4,local_148,&local_70);
              cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
              if (cVar2 != '\0') goto LAB_001480a4;
              if (lVar7 != 0) {
                if ((local_150 == 0) &&
                   (uVar5 = FUN_001272e0(param_1,local_a0 + 3,&local_150,0,"android/webkit/WebView",
                                         "setWebViewClient","(Landroid/webkit/WebViewClient;)V"),
                   (uVar5 & 1) != 0)) goto LAB_001480a4;
                local_70 = uVar4;
                (**(code **)(*param_1 + 0x1f8))(param_1,lVar7,local_150,&local_70);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if ((cVar2 != '\0') ||
                   ((local_d0 == 0 &&
                    (uVar5 = FUN_001274cc(param_1,local_a0 + 4,&local_d0,0,&DAT_0011b446,
                                          &DAT_0011a6bb,"Landroid/webkit/WebView;"),
                    (uVar5 & 1) != 0)))) goto LAB_001480a4;
                lVar6 = (**(code **)(*param_1 + 0x2f8))(param_1,uVar3,local_d0);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if (cVar2 != '\0') goto LAB_001480a4;
                (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
                (**(code **)(*param_1 + 0xb8))(param_1,uVar4);
                uVar4 = (**(code **)(*param_1 + 0x580))(param_1,0x10);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if ((cVar2 != '\0') ||
                   (((**(code **)(*param_1 + 0x680))(param_1,uVar4,0,0x10,&DAT_0011c975),
                    local_158 == 0 &&
                    (uVar5 = FUN_001272e0(param_1,&local_b0,&local_158,1,&DAT_0011567b,&DAT_0011a6bb
                                          ,"([B)Ljava/lang/String;"), (uVar5 & 1) != 0))))
                goto LAB_001480a4;
                local_70 = uVar4;
                uVar5 = (**(code **)(*param_1 + 0x3a0))(param_1,local_b0,local_158,&local_70);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if (cVar2 != '\0') goto LAB_001480a4;
                if (uVar4 != 0) {
                  (**(code **)(*param_1 + 0xb8))(param_1,uVar4);
                }
                if ((local_160 == 0) &&
                   (uVar4 = FUN_001272e0(param_1,&local_b8,&local_160,1,&DAT_00119a18,&DAT_0011ac0e,
                                         "(Ljava/lang/String;)Ljava/lang/String;"), (uVar4 & 1) != 0
                   )) goto LAB_001480a4;
                local_70 = uVar5;
                lVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_b8,local_160,&local_70);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if (cVar2 != '\0') goto LAB_001480a4;
                if (uVar5 != 0) {
                  (**(code **)(*param_1 + 0xb8))(param_1,uVar5);
                }
                uVar4 = (**(code **)(*param_1 + 0x580))(param_1,0x3a);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if (cVar2 != '\0') goto LAB_001480a4;
                (**(code **)(*param_1 + 0x680))(param_1,uVar4,0,0x3a,&DAT_0011c985);
                uVar5 = FUN_001272e0(param_1,&local_c0,&local_168,1,&DAT_00116867,&DAT_0011a6bb,
                                     "([BLjava/lang/String;D)Ljava/lang/String;");
                if ((uVar5 & 1) != 0) goto LAB_001480a4;
                local_60 = 0x41d6960eb2400000;
                local_70 = uVar4;
                lStack_68 = lVar7;
                uVar4 = (**(code **)(*param_1 + 0x3a0))(param_1,local_c0,local_168,&local_70);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if (cVar2 != '\0') goto LAB_001480a4;
                if (lVar7 != 0) {
                  (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
                }
                if (lVar6 != 0) {
                  uVar5 = FUN_001272e0(param_1,local_a0 + 3,&local_170,0,"android/webkit/WebView",
                                       "loadUrl","(Ljava/lang/String;)V");
                  if ((uVar5 & 1) != 0) goto LAB_001480a4;
                  local_70 = uVar4;
                  (**(code **)(*param_1 + 0x1f8))(param_1,lVar6,local_170,&local_70);
                  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                  if ((cVar2 != '\0') ||
                     ((local_d8 == 0 &&
                      (uVar5 = FUN_001274cc(param_1,local_a0 + 4,&local_d8,0,&DAT_0011b446,
                                            &DAT_001156e1,"Landroid/widget/FrameLayout;"),
                      (uVar5 & 1) != 0)))) goto LAB_001480a4;
                  lVar7 = (**(code **)(*param_1 + 0x2f8))(param_1,uVar3,local_d8);
                  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                  if (cVar2 != '\0') goto LAB_001480a4;
                  (**(code **)(*param_1 + 0xb8))(param_1,lVar6);
                  if (uVar4 != 0) {
                    (**(code **)(*param_1 + 0xb8))(param_1,uVar4);
                  }
                  uVar4 = FUN_00127120(param_1,&local_c8,&DAT_0011b639);
                  if ((uVar4 & 1) != 0) goto LAB_001480a4;
                  uVar4 = (**(code **)(*param_1 + 0xd8))(param_1,local_c8);
                  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                  if (cVar2 != '\0') goto LAB_001480a4;
                  if (uVar4 != 0) {
                    uVar5 = FUN_001272e0(param_1,&local_c8,&local_178,0,&DAT_0011b639,"<init>",
                                         &DAT_0011aa1b);
                    if ((uVar5 & 1) != 0) goto LAB_001480a4;
                    local_70 = uVar3;
                    (**(code **)(*param_1 + 0x1f8))(param_1,uVar4,local_178,&local_70);
                    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                    if (cVar2 != '\0') goto LAB_001480a4;
                    if (lVar7 != 0) {
                      uVar3 = FUN_001272e0(param_1,local_a0 + 2,&local_180,0,
                                           "android/widget/FrameLayout","setOnTouchListener",
                                           "(Landroid/view/View$OnTouchListener;)V");
                      if ((uVar3 & 1) == 0) {
                        local_70 = uVar4;
                        (**(code **)(*param_1 + 0x1f8))(param_1,lVar7,local_180,&local_70);
                        (**(code **)(*param_1 + 0x720))(param_1);
                      }
                      goto LAB_001480a4;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_00126cfc(param_1,"java/lang/NullPointerException","NullPointerException");
LAB_001480a4:
  if (*(long *)(lVar1 + 0x28) != local_58) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}




##### Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_08c01_05bb6_04eca_0591c_06241_0821f_05b50_04f55_05904_076f8_0601d_0660e_06708_0697c_0064e_onCreate__Landroid_os_Bundle_2 #####
/* ===== Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_08c01_05bb6_04eca_0591c_06241_0821f_05b50_04f55_05904_076f8_0601d_0660e_06708_0697c_0064e_onCreate__Landroid_os_Bundle_2 @ 00160ee4 ==== */
/* signature: undefined Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_08c01_05bb6_04eca_0591c_06241_0821f_05b50_04f55_05904_076f8_0601d_0660e_06708_0697c_0064e_onCreate__Landroid_os_Bundle_2(void) */

/* WARNING: Type propagation algorithm not settling */

void Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_08c01_05bb6_04eca_0591c_06241_0821f_05b50_04f55_05904_076f8_0601d_0660e_06708_0697c_0064e_onCreate__Landroid_os_Bundle_2
               (long *param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  char cVar2;
  char cVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  undefined8 local_1b0;
  undefined8 local_1a8;
  long local_1a0;
  long local_198;
  long local_190;
  long local_188;
  long local_180;
  long local_178;
  long local_170;
  long local_168;
  long local_160;
  long local_158;
  long local_150;
  long local_148;
  long local_140;
  long local_138;
  undefined8 local_130;
  long local_128;
  long local_120;
  long local_118;
  long local_110;
  long local_108;
  long local_100;
  long local_f8;
  long local_f0;
  undefined8 local_e8;
  undefined8 local_e0;
  long local_d8 [11];
  long local_80;
  ulong local_78;
  undefined8 local_70;
  long local_68;
  
  lVar1 = tpidr_el0;
  local_68 = *(long *)(lVar1 + 0x28);
  local_d8[9] = 0;
  local_d8[10] = 0;
  local_d8[7] = 0;
  local_d8[8] = 0;
  local_d8[5] = 0;
  local_d8[6] = 0;
  local_d8[3] = 0;
  local_d8[4] = 0;
  local_d8[1] = 0;
  local_d8[2] = 0;
  local_e0 = 0;
  local_d8[0] = 0;
  local_f0 = 0;
  local_e8 = 0;
  local_100 = 0;
  local_f8 = 0;
  local_110 = 0;
  local_108 = 0;
  local_120 = 0;
  local_118 = 0;
  local_130 = 0;
  local_128 = 0;
  local_140 = 0;
  local_138 = 0;
  local_150 = 0;
  local_148 = 0;
  local_160 = 0;
  local_158 = 0;
  local_170 = 0;
  local_168 = 0;
  local_180 = 0;
  local_178 = 0;
  local_190 = 0;
  local_188 = 0;
  local_1a0 = 0;
  local_198 = 0;
  local_1b0 = 0;
  local_1a8 = 0;
  lVar4 = (**(code **)(*param_1 + 200))();
  lVar5 = (**(code **)(*param_1 + 200))(param_1,param_3);
  if (lVar4 == 0) goto LAB_00162c7c;
  uVar6 = FUN_001272e0(param_1,local_d8 + 10,&local_130,0,"androidx/appcompat/app/AppCompatActivity"
                       ,"onCreate","(Landroid/os/Bundle;)V");
  if ((uVar6 & 1) != 0) goto LAB_00162c94;
  local_80 = lVar5;
  (**(code **)(*param_1 + 0x2e8))(param_1,lVar4,local_d8[10],local_130,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_138 == 0 &&
      (uVar6 = FUN_001272e0(param_1,local_d8 + 9,&local_138,0,&DAT_001179aa,"setContentView",
                            &DAT_00117730), (uVar6 & 1) != 0)))) goto LAB_00162c94;
  local_80 = CONCAT44(local_80._4_4_,0x7f0b0074);
  (**(code **)(*param_1 + 0x1f8))(param_1,lVar4,local_138,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_140 == 0 &&
      (uVar6 = FUN_001272e0(param_1,local_d8 + 9,&local_140,0,&DAT_001179aa,"findViewById",
                            "(I)Landroid/view/View;"), (uVar6 & 1) != 0)))) goto LAB_00162c94;
  local_80 = CONCAT44(local_80._4_4_,0x7f0800c2);
  lVar5 = (**(code **)(*param_1 + 0x120))(param_1,lVar4,local_140,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (((cVar2 != '\0') ||
      ((((local_d8[8] == 0 &&
         (uVar6 = FUN_00127120(param_1,local_d8 + 8,"android/widget/EditText"), (uVar6 & 1) != 0))
        || (uVar6 = FUN_0012708c(param_1,lVar5,local_d8[8],"android/widget/EditText"),
           (uVar6 & 1) != 0)) || (cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0')))
      ) || ((local_f0 == 0 &&
            (uVar6 = FUN_001274cc(param_1,local_d8 + 9,&local_f0,0,&DAT_001179aa,&DAT_00119e13,
                                  "Landroid/widget/EditText;"), (uVar6 & 1) != 0))))
  goto LAB_00162c94;
  (**(code **)(*param_1 + 0x340))(param_1,lVar4,local_f0,lVar5);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_140 == 0 &&
      (uVar6 = FUN_001272e0(param_1,local_d8 + 9,&local_140,0,&DAT_001179aa,"findViewById",
                            "(I)Landroid/view/View;"), (uVar6 & 1) != 0)))) goto LAB_00162c94;
  local_80 = CONCAT44(local_80._4_4_,0x7f08023f);
  lVar7 = (**(code **)(*param_1 + 0x120))(param_1,lVar4,local_140,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (lVar5 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
  }
  if ((((local_d8[7] == 0) &&
       (uVar6 = FUN_00127120(param_1,local_d8 + 7,"android/widget/TextView"), (uVar6 & 1) != 0)) ||
      (uVar6 = FUN_0012708c(param_1,lVar7,local_d8[7],"android/widget/TextView"), (uVar6 & 1) != 0))
     || ((cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0' ||
         ((local_f8 == 0 &&
          (uVar6 = FUN_001274cc(param_1,local_d8 + 9,&local_f8,0,&DAT_001179aa,&DAT_001188bc,
                                "Landroid/widget/TextView;"), (uVar6 & 1) != 0))))))
  goto LAB_00162c94;
  (**(code **)(*param_1 + 0x340))(param_1,lVar4,local_f8,lVar7);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_140 == 0 &&
      (uVar6 = FUN_001272e0(param_1,local_d8 + 9,&local_140,0,&DAT_001179aa,"findViewById",
                            "(I)Landroid/view/View;"), (uVar6 & 1) != 0)))) goto LAB_00162c94;
  local_80 = CONCAT44(local_80._4_4_,0x7f08006f);
  lVar5 = (**(code **)(*param_1 + 0x120))(param_1,lVar4,local_140,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (lVar7 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
  }
  if ((((local_d8[6] == 0) &&
       (uVar6 = FUN_00127120(param_1,local_d8 + 6,"android/widget/Button"), (uVar6 & 1) != 0)) ||
      (uVar6 = FUN_0012708c(param_1,lVar5,local_d8[6],"android/widget/Button"), (uVar6 & 1) != 0))
     || ((cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0' ||
         ((local_100 == 0 &&
          (uVar6 = FUN_001274cc(param_1,local_d8 + 9,&local_100,0,&DAT_001179aa,&DAT_00117cb9,
                                "Landroid/widget/Button;"), (uVar6 & 1) != 0))))))
  goto LAB_00162c94;
  (**(code **)(*param_1 + 0x340))(param_1,lVar4,local_100,lVar5);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_140 == 0 &&
      (uVar6 = FUN_001272e0(param_1,local_d8 + 9,&local_140,0,&DAT_001179aa,"findViewById",
                            "(I)Landroid/view/View;"), (uVar6 & 1) != 0)))) goto LAB_00162c94;
  local_80 = CONCAT44(local_80._4_4_,0x7f08006a);
  lVar7 = (**(code **)(*param_1 + 0x120))(param_1,lVar4,local_140,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (lVar5 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
  }
  if (((((local_d8[6] == 0) &&
        (uVar6 = FUN_00127120(param_1,local_d8 + 6,"android/widget/Button"), (uVar6 & 1) != 0)) ||
       (uVar6 = FUN_0012708c(param_1,lVar7,local_d8[6],"android/widget/Button"), (uVar6 & 1) != 0))
      || (cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0')) ||
     ((local_108 == 0 &&
      (uVar6 = FUN_001274cc(param_1,local_d8 + 9,&local_108,0,&DAT_001179aa,&DAT_001151d6,
                            "Landroid/widget/Button;"), (uVar6 & 1) != 0)))) goto LAB_00162c94;
  (**(code **)(*param_1 + 0x340))(param_1,lVar4,local_108,lVar7);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_140 == 0 &&
      (uVar6 = FUN_001272e0(param_1,local_d8 + 9,&local_140,0,&DAT_001179aa,"findViewById",
                            "(I)Landroid/view/View;"), (uVar6 & 1) != 0)))) goto LAB_00162c94;
  local_80 = CONCAT44(local_80._4_4_,0x7f080070);
  lVar5 = (**(code **)(*param_1 + 0x120))(param_1,lVar4,local_140,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (lVar7 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
  }
  if ((((local_d8[6] == 0) &&
       (uVar6 = FUN_00127120(param_1,local_d8 + 6,"android/widget/Button"), (uVar6 & 1) != 0)) ||
      (uVar6 = FUN_0012708c(param_1,lVar5,local_d8[6],"android/widget/Button"), (uVar6 & 1) != 0))
     || ((cVar2 = (**(code **)(*param_1 + 0x720))(param_1), cVar2 != '\0' ||
         ((local_110 == 0 &&
          (uVar6 = FUN_001274cc(param_1,local_d8 + 9,&local_110,0,&DAT_001179aa,&DAT_001157b8,
                                "Landroid/widget/Button;"), (uVar6 & 1) != 0))))))
  goto LAB_00162c94;
  (**(code **)(*param_1 + 0x340))(param_1,lVar4,local_110,lVar5);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (lVar5 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
  }
  lVar5 = (**(code **)(*param_1 + 0x580))(param_1,0x10);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     (((**(code **)(*param_1 + 0x680))(param_1,lVar5,0,0x10,&DAT_0011d241), local_148 == 0 &&
      (uVar6 = FUN_001272e0(param_1,local_d8 + 5,&local_148,1,&DAT_0011567b,&DAT_0011a6bb,
                            "([B)Ljava/lang/String;"), (uVar6 & 1) != 0)))) goto LAB_00162c94;
  local_80 = lVar5;
  lVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[5],local_148,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (lVar5 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
  }
  if ((local_150 == 0) &&
     (uVar6 = FUN_001272e0(param_1,local_d8 + 4,&local_150,1,&DAT_00119a18,&DAT_0011ac0e,
                           "(Ljava/lang/String;)Ljava/lang/String;"), (uVar6 & 1) != 0))
  goto LAB_00162c94;
  local_80 = lVar7;
  uVar6 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[4],local_150,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (lVar7 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
  }
  lVar5 = (**(code **)(*param_1 + 0x580))(param_1,4);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     (((**(code **)(*param_1 + 0x680))(param_1,lVar5,0,4,&DAT_0011d251), local_158 == 0 &&
      (uVar8 = FUN_001272e0(param_1,local_d8 + 3,&local_158,1,&DAT_00116867,&DAT_0011a6bb,
                            "([BLjava/lang/String;J)Ljava/lang/String;"), (uVar8 & 1) != 0))))
  goto LAB_00162c94;
  local_70 = 0xffffffffce82d995;
  local_80 = lVar5;
  local_78 = uVar6;
  lVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[3],local_158,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (uVar6 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,uVar6);
  }
  if ((local_160 == 0) &&
     (uVar6 = FUN_001272e0(param_1,local_d8 + 9,&local_160,0,&DAT_001179aa,"getSharedPreferences",
                           "(Ljava/lang/String;I)Landroid/content/SharedPreferences;"),
     (uVar6 & 1) != 0)) goto LAB_00162c94;
  local_78 = local_78 & 0xffffffff00000000;
  local_80 = lVar7;
  lVar9 = (**(code **)(*param_1 + 0x120))(param_1,lVar4,local_160,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (lVar7 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
  }
  if ((local_118 == 0) &&
     (uVar6 = FUN_001274cc(param_1,local_d8 + 9,&local_118,0,&DAT_001179aa,&DAT_00115791,
                           "Landroid/content/SharedPreferences;"), (uVar6 & 1) != 0))
  goto LAB_00162c94;
  (**(code **)(*param_1 + 0x340))(param_1,lVar4,local_118,lVar9);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_168 == 0 &&
      (uVar6 = FUN_001272e0(param_1,local_d8 + 9,&local_168,0,&DAT_001179aa,&DAT_0011a9e0,
                            "()Ljava/lang/String;"), (uVar6 & 1) != 0)))) goto LAB_00162c94;
  lVar7 = (**(code **)(*param_1 + 0x120))(param_1,lVar4,local_168,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (lVar9 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
  }
  if ((local_120 == 0) &&
     (uVar6 = FUN_001274cc(param_1,local_d8 + 9,&local_120,0,&DAT_001179aa,&DAT_0011b96f,
                           "Ljava/lang/String;"), (uVar6 & 1) != 0)) goto LAB_00162c94;
  (**(code **)(*param_1 + 0x340))(param_1,lVar4,local_120,lVar7);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     ((local_118 == 0 &&
      (uVar6 = FUN_001274cc(param_1,local_d8 + 9,&local_118,0,&DAT_001179aa,&DAT_00115791,
                            "Landroid/content/SharedPreferences;"), (uVar6 & 1) != 0))))
  goto LAB_00162c94;
  lVar9 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar4,local_118);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (lVar7 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
  }
  if (lVar5 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
  }
  lVar5 = (**(code **)(*param_1 + 0x580))(param_1,0x10);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     (((**(code **)(*param_1 + 0x680))(param_1,lVar5,0,0x10,&DAT_0011d255), local_148 == 0 &&
      (uVar6 = FUN_001272e0(param_1,local_d8 + 5,&local_148,1,&DAT_0011567b,&DAT_0011a6bb,
                            "([B)Ljava/lang/String;"), (uVar6 & 1) != 0)))) goto LAB_00162c94;
  local_80 = lVar5;
  lVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[5],local_148,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (lVar5 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
  }
  if ((local_150 == 0) &&
     (uVar6 = FUN_001272e0(param_1,local_d8 + 4,&local_150,1,&DAT_00119a18,&DAT_0011ac0e,
                           "(Ljava/lang/String;)Ljava/lang/String;"), (uVar6 & 1) != 0))
  goto LAB_00162c94;
  local_80 = lVar7;
  uVar6 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[4],local_150,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (lVar7 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
  }
  lVar5 = (**(code **)(*param_1 + 0x580))(param_1,8);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if ((cVar2 != '\0') ||
     (((**(code **)(*param_1 + 0x680))(param_1,lVar5,0,8,&DAT_0011d265), local_170 == 0 &&
      (uVar8 = FUN_001272e0(param_1,local_d8 + 3,&local_170,1,&DAT_00116867,&DAT_0011a6bb,
                            "([BLjava/lang/String;F)Ljava/lang/String;"), (uVar8 & 1) != 0))))
  goto LAB_00162c94;
  local_70 = CONCAT44(local_70._4_4_,0xcee39339);
  local_80 = lVar5;
  local_78 = uVar6;
  lVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[3],local_170,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (uVar6 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,uVar6);
  }
  if (lVar5 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
  }
  lVar5 = (**(code **)(*param_1 + 0x538))(param_1,&DAT_0011ac2d);
  if ((local_150 == 0) &&
     (uVar6 = FUN_001272e0(param_1,local_d8 + 4,&local_150,1,&DAT_00119a18,&DAT_0011ac0e,
                           "(Ljava/lang/String;)Ljava/lang/String;"), (uVar6 & 1) != 0))
  goto LAB_00162c94;
  local_80 = lVar5;
  uVar6 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[4],local_150,&local_80);
  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
  if (cVar2 != '\0') goto LAB_00162c94;
  if (lVar5 != 0) {
    (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
  }
  if (lVar9 != 0) {
    if ((local_178 == 0) &&
       (uVar8 = FUN_001272e0(param_1,local_d8 + 2,&local_178,0,"android/content/SharedPreferences",
                             "getString","(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")
       , (uVar8 & 1) != 0)) goto LAB_00162c94;
    local_80 = lVar7;
    local_78 = uVar6;
    lVar5 = (**(code **)(*param_1 + 0x120))(param_1,lVar9,local_178,&local_80);
    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
    if (cVar2 != '\0') goto LAB_00162c94;
    (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
    if (lVar5 != 0) {
      if ((local_180 == 0) &&
         (uVar8 = FUN_001272e0(param_1,local_d8 + 1,&local_180,0,"java/lang/String","isEmpty",
                               &DAT_0011941d), (uVar8 & 1) != 0)) goto LAB_00162c94;
      cVar2 = (**(code **)(*param_1 + 0x138))(param_1,lVar5,local_180,&local_80);
      cVar3 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar3 != '\0') goto LAB_00162c94;
      if (cVar2 == '\0') {
        if ((local_f0 == 0) &&
           (uVar8 = FUN_001274cc(param_1,local_d8 + 9,&local_f0,0,&DAT_001179aa,&DAT_00119e13,
                                 "Landroid/widget/EditText;"), (uVar8 & 1) != 0)) goto LAB_00162c94;
        lVar9 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar4,local_f0);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar2 != '\0') goto LAB_00162c94;
        if (lVar7 != 0) {
          (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
        }
        if (lVar9 == 0) goto LAB_00162c7c;
        if ((local_188 == 0) &&
           (uVar8 = FUN_001272e0(param_1,local_d8 + 8,&local_188,0,"android/widget/EditText",
                                 "setText","(Ljava/lang/CharSequence;)V"), (uVar8 & 1) != 0))
        goto LAB_00162c94;
        local_80 = lVar5;
        (**(code **)(*param_1 + 0x1f8))(param_1,lVar9,local_188,&local_80);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        lVar7 = lVar9;
        if (cVar2 != '\0') goto LAB_00162c94;
      }
      if ((local_118 == 0) &&
         (uVar8 = FUN_001274cc(param_1,local_d8 + 9,&local_118,0,&DAT_001179aa,&DAT_00115791,
                               "Landroid/content/SharedPreferences;"), (uVar8 & 1) != 0))
      goto LAB_00162c94;
      lVar9 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar4,local_118);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_00162c94;
      (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
      if (lVar7 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
      }
      lVar5 = (**(code **)(*param_1 + 0x580))(param_1,0x10);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if ((cVar2 != '\0') ||
         (((**(code **)(*param_1 + 0x680))(param_1,lVar5,0,0x10,&DAT_0011d26d), local_148 == 0 &&
          (uVar8 = FUN_001272e0(param_1,local_d8 + 5,&local_148,1,&DAT_0011567b,&DAT_0011a6bb,
                                "([B)Ljava/lang/String;"), (uVar8 & 1) != 0)))) goto LAB_00162c94;
      local_80 = lVar5;
      lVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[5],local_148,&local_80);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_00162c94;
      if (lVar5 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
      }
      if ((local_150 == 0) &&
         (uVar8 = FUN_001272e0(param_1,local_d8 + 4,&local_150,1,&DAT_00119a18,&DAT_0011ac0e,
                               "(Ljava/lang/String;)Ljava/lang/String;"), (uVar8 & 1) != 0))
      goto LAB_00162c94;
      local_80 = lVar7;
      uVar8 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[4],local_150,&local_80);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_00162c94;
      if (lVar7 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
      }
      if (uVar6 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,uVar6);
      }
      lVar5 = (**(code **)(*param_1 + 0x580))(param_1,0xc);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if ((cVar2 != '\0') ||
         (((**(code **)(*param_1 + 0x680))(param_1,lVar5,0,0xc,&DAT_0011d27d), local_170 == 0 &&
          (uVar6 = FUN_001272e0(param_1,local_d8 + 3,&local_170,1,&DAT_00116867,&DAT_0011a6bb,
                                "([BLjava/lang/String;F)Ljava/lang/String;"), (uVar6 & 1) != 0))))
      goto LAB_00162c94;
      local_70 = CONCAT44(local_70._4_4_,0xceadd3cd);
      local_80 = lVar5;
      local_78 = uVar8;
      lVar7 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[3],local_170,&local_80);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_00162c94;
      if (uVar8 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,uVar8);
      }
      if (lVar5 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
      }
      lVar5 = (**(code **)(*param_1 + 0x538))(param_1,&DAT_0011ac2d);
      if ((local_150 == 0) &&
         (uVar6 = FUN_001272e0(param_1,local_d8 + 4,&local_150,1,&DAT_00119a18,&DAT_0011ac0e,
                               "(Ljava/lang/String;)Ljava/lang/String;"), (uVar6 & 1) != 0))
      goto LAB_00162c94;
      local_80 = lVar5;
      uVar6 = (**(code **)(*param_1 + 0x3a0))(param_1,local_d8[4],local_150,&local_80);
      cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
      if (cVar2 != '\0') goto LAB_00162c94;
      if (lVar5 != 0) {
        (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
      }
      if (lVar9 != 0) {
        if ((local_178 == 0) &&
           (uVar8 = FUN_001272e0(param_1,local_d8 + 2,&local_178,0,
                                 "android/content/SharedPreferences","getString",
                                 "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;"),
           (uVar8 & 1) != 0)) goto LAB_00162c94;
        local_80 = lVar7;
        local_78 = uVar6;
        lVar5 = (**(code **)(*param_1 + 0x120))(param_1,lVar9,local_178,&local_80);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 != '\0') ||
           (((**(code **)(*param_1 + 0xb8))(param_1,lVar9), local_128 == 0 &&
            (uVar6 = FUN_001274cc(param_1,local_d8 + 9,&local_128,0,&DAT_001179aa,&DAT_0011aceb,
                                  "Ljava/lang/String;"), (uVar6 & 1) != 0)))) goto LAB_00162c94;
        (**(code **)(*param_1 + 0x340))(param_1,lVar4,local_128,lVar5);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 != '\0') ||
           ((local_128 == 0 &&
            (uVar6 = FUN_001274cc(param_1,local_d8 + 9,&local_128,0,&DAT_001179aa,&DAT_0011aceb,
                                  "Ljava/lang/String;"), (uVar6 & 1) != 0)))) goto LAB_00162c94;
        lVar9 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar4,local_128);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if (cVar2 != '\0') goto LAB_00162c94;
        if (lVar5 != 0) {
          (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
        }
        if (lVar9 != 0) {
          if ((local_180 == 0) &&
             (uVar6 = FUN_001272e0(param_1,local_d8 + 1,&local_180,0,"java/lang/String","isEmpty",
                                   &DAT_0011941d), (uVar6 & 1) != 0)) goto LAB_00162c94;
          cVar2 = (**(code **)(*param_1 + 0x138))(param_1,lVar9,local_180,&local_80);
          cVar3 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar3 != '\0') goto LAB_00162c94;
          if (cVar2 != '\0') {
            if ((local_190 == 0) &&
               (uVar6 = FUN_001272e0(param_1,local_d8 + 9,&local_190,0,&DAT_001179aa,&DAT_00115040,
                                     &DAT_00117ed6), (uVar6 & 1) != 0)) goto LAB_00162c94;
            (**(code **)(*param_1 + 0x1f8))(param_1,lVar4,local_190,&local_80);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_00162c94;
          }
          if ((local_108 == 0) &&
             (uVar6 = FUN_001274cc(param_1,local_d8 + 9,&local_108,0,&DAT_001179aa,&DAT_001151d6,
                                   "Landroid/widget/Button;"), (uVar6 & 1) != 0)) goto LAB_00162c94;
          lVar5 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar4,local_108);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar2 != '\0') goto LAB_00162c94;
          (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
          if (lVar7 != 0) {
            (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
          }
          if ((local_d8[0] == 0) &&
             (uVar6 = FUN_00127120(param_1,local_d8,&DAT_00118271), (uVar6 & 1) != 0))
          goto LAB_00162c94;
          lVar7 = (**(code **)(*param_1 + 0xd8))(param_1,local_d8[0]);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if (cVar2 != '\0') goto LAB_00162c94;
          if (lVar7 != 0) {
            if ((local_198 == 0) &&
               (uVar6 = FUN_001272e0(param_1,local_d8,&local_198,0,&DAT_00118271,"<init>",
                                     &DAT_00116441), (uVar6 & 1) != 0)) goto LAB_00162c94;
            local_80 = lVar4;
            (**(code **)(*param_1 + 0x1f8))(param_1,lVar7,local_198,&local_80);
            cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
            if (cVar2 != '\0') goto LAB_00162c94;
            if (lVar5 != 0) {
              if ((local_1a0 == 0) &&
                 (uVar6 = FUN_001272e0(param_1,local_d8 + 6,&local_1a0,0,"android/widget/Button",
                                       "setOnClickListener","(Landroid/view/View$OnClickListener;)V"
                                      ), (uVar6 & 1) != 0)) goto LAB_00162c94;
              local_80 = lVar7;
              (**(code **)(*param_1 + 0x1f8))(param_1,lVar5,local_1a0,&local_80);
              cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
              if ((cVar2 != '\0') ||
                 ((local_100 == 0 &&
                  (uVar6 = FUN_001274cc(param_1,local_d8 + 9,&local_100,0,&DAT_001179aa,
                                        &DAT_00117cb9,"Landroid/widget/Button;"), (uVar6 & 1) != 0))
                 )) goto LAB_00162c94;
              lVar9 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar4,local_100);
              cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
              if (cVar2 != '\0') goto LAB_00162c94;
              (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
              (**(code **)(*param_1 + 0xb8))(param_1,lVar7);
              uVar6 = FUN_00127120(param_1,&local_e0,&DAT_001188f4);
              if ((uVar6 & 1) != 0) goto LAB_00162c94;
              lVar5 = (**(code **)(*param_1 + 0xd8))(param_1,local_e0);
              cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
              if (cVar2 != '\0') goto LAB_00162c94;
              if (lVar5 != 0) {
                uVar6 = FUN_001272e0(param_1,&local_e0,&local_1a8,0,&DAT_001188f4,"<init>",
                                     &DAT_00116441);
                if ((uVar6 & 1) != 0) goto LAB_00162c94;
                local_80 = lVar4;
                (**(code **)(*param_1 + 0x1f8))(param_1,lVar5,local_1a8,&local_80);
                cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                if (cVar2 != '\0') goto LAB_00162c94;
                if (lVar9 != 0) {
                  if ((local_1a0 == 0) &&
                     (uVar6 = FUN_001272e0(param_1,local_d8 + 6,&local_1a0,0,"android/widget/Button"
                                           ,"setOnClickListener",
                                           "(Landroid/view/View$OnClickListener;)V"),
                     (uVar6 & 1) != 0)) goto LAB_00162c94;
                  local_80 = lVar5;
                  (**(code **)(*param_1 + 0x1f8))(param_1,lVar9,local_1a0,&local_80);
                  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                  if ((cVar2 != '\0') ||
                     ((local_110 == 0 &&
                      (uVar6 = FUN_001274cc(param_1,local_d8 + 9,&local_110,0,&DAT_001179aa,
                                            &DAT_001157b8,"Landroid/widget/Button;"),
                      (uVar6 & 1) != 0)))) goto LAB_00162c94;
                  lVar7 = (**(code **)(*param_1 + 0x2f8))(param_1,lVar4,local_110);
                  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                  if (cVar2 != '\0') goto LAB_00162c94;
                  (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
                  (**(code **)(*param_1 + 0xb8))(param_1,lVar5);
                  uVar6 = FUN_00127120(param_1,&local_e8,&DAT_00116dd8);
                  if ((uVar6 & 1) != 0) goto LAB_00162c94;
                  lVar5 = (**(code **)(*param_1 + 0xd8))(param_1,local_e8);
                  cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                  if (cVar2 != '\0') goto LAB_00162c94;
                  if (lVar5 != 0) {
                    uVar6 = FUN_001272e0(param_1,&local_e8,&local_1b0,0,&DAT_00116dd8,"<init>",
                                         &DAT_00116441);
                    if ((uVar6 & 1) != 0) goto LAB_00162c94;
                    local_80 = lVar4;
                    (**(code **)(*param_1 + 0x1f8))(param_1,lVar5,local_1b0,&local_80);
                    cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
                    if (cVar2 != '\0') goto LAB_00162c94;
                    if (lVar7 != 0) {
                      if ((local_1a0 != 0) ||
                         (uVar6 = FUN_001272e0(param_1,local_d8 + 6,&local_1a0,0,
                                               "android/widget/Button","setOnClickListener",
                                               "(Landroid/view/View$OnClickListener;)V"),
                         (uVar6 & 1) == 0)) {
                        local_80 = lVar5;
                        (**(code **)(*param_1 + 0x1f8))(param_1,lVar7,local_1a0,&local_80);
                        (**(code **)(*param_1 + 0x720))(param_1);
                      }
                      goto LAB_00162c94;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_00162c7c:
  FUN_00126cfc(param_1,"java/lang/NullPointerException","NullPointerException");
LAB_00162c94:
  if (*(long *)(lVar1 + 0x28) != local_68) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}




##### Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_0957f_098ce_04e07_091cc_09001_079cb_096c1_05bf9_06b64_053ef_04ee5_09163_09ad8_0697c_0064e_onCreate__Landroid_os_Bundle_2 #####
/* ===== Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_0957f_098ce_04e07_091cc_09001_079cb_096c1_05bf9_06b64_053ef_04ee5_09163_09ad8_0697c_0064e_onCreate__Landroid_os_Bundle_2 @ 0016c528 ==== */
/* signature: undefined Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_0957f_098ce_04e07_091cc_09001_079cb_096c1_05bf9_06b64_053ef_04ee5_09163_09ad8_0697c_0064e_onCreate__Landroid_os_Bundle_2(void) */

void Java_com_Sx2_Team_Ban__0541b_04e0d_089c1_09ad8_05802_0660e_0955c_060b2_0767d_053d1_0957f_098ce_04e07_091cc_09001_079cb_096c1_05bf9_06b64_053ef_04ee5_09163_09ad8_0697c_0064e_onCreate__Landroid_os_Bundle_2
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
         (uVar5 = FUN_001272e0(param_1,&uStack_50,&local_60,0,&DAT_00119421,"setContentView",
                               &DAT_00117730), (uVar5 & 1) == 0)) {
        local_40 = CONCAT44(local_40._4_4_,0x7f0b003f);
        (**(code **)(*param_1 + 0x1f8))(param_1,lVar3,local_60,&local_40);
        cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
        if ((cVar2 == '\0') &&
           (uVar5 = FUN_001272e0(param_1,&uStack_50,&local_68,0,&DAT_00119421,&DAT_001188bc,
                                 "(Landroid/os/Bundle;)V"), (uVar5 & 1) == 0)) {
          local_40 = uVar4;
          (**(code **)(*param_1 + 0x1f8))(param_1,lVar3,local_68,&local_40);
          cVar2 = (**(code **)(*param_1 + 0x720))(param_1);
          if ((cVar2 == '\0') &&
             (uVar5 = FUN_001272e0(param_1,&uStack_50,&local_70,0,&DAT_00119421,&DAT_00115040,
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



