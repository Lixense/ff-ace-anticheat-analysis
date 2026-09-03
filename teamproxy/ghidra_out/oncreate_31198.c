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




