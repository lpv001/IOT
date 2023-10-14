//This field is for create action of  button in the gui

// power button
public void PowerON()
{ 
  myPort.write('C');
  myPort.write(1);
  myKnobB.setValue(0);
  println(myKnobB.getValue());
  Power1 = 0;
}

// power button
public void PowerOFF()
{ 
  myPort.write('C');
  myPort.write(4);
  myKnobB.setValue(5);
  println(myKnobB.getValue());
  Power1 = 1;
}

public void tlm500(int theValue) 
{
  myPort.write('C');
  myPort.write(2);
}

public void tlm20(int theValue)
{
  myPort.write('C');
  myPort.write(3);
}

public void BMPOn()
{
  //myPort.write('C');
  //myPort.write(4);
  
  PressureChart.push("pressure", pressure);
  AlttiChart.push("alttitude", alttitude);
  Value1 = 1;
}

public void BMPOff()
{
  //myPort.write('C');
  //myPort.write(5);
  PressureChart.push("pressure", 0);
  AlttiChart.push("alttitude", 0);
  Value1 = 0;
}  
