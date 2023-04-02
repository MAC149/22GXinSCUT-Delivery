extern String QRcode,WL1_pose,WL2_pose;
void OG_Up_Test()
{
  QRcode="123+321";
  WL1_pose="123";
  OG_Action(1);
}

void OG_Down_Test()
{
  QRcode="123+321";
  WL2_pose="123";
  OG_Action(2);
}

void RM_Test()
{
  QRcode="123+321";
  RM_Action(1);
}

void SM_Test_Ground()
{
  QRcode="123+321";
  SM_Action(1);
}

void SM_Test_Stack()
{
  QRcode="123+321";
  SM_Action(2);
}

void MPU3Ang()
{
  adjust_angle(90);
  adjust_angle(-90);
  adjust_angle(0);
}