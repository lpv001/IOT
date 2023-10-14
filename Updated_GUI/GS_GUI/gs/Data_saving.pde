////import processing.serial.*;
////Serial myPort;



//void tablesetup() {

//  table = new Table();
//  table.addColumn("id");
//  table.addColumn("AccX");
//  table.addColumn("AccY");
//  table.addColumn("AccZ");
//  table.addColumn("GyroX");
//  table.addColumn("GyroY");
//  table.addColumn("GyroZ");
//  table.addColumn("Yaw");
//  table.addColumn("Pitch");
//  table.addColumn("Roll");
//  table.addColumn("Pressure");
//  table.addColumn("Temperature");
//  table.addColumn("Alttitude");

//}
//void tabledraw() {


//   TableRow newRow = table.addRow();
//  newRow.setInt("id", table.getRowCount() - 1);
//  newRow.setFloat("AccX", acceX);
//  newRow.setFloat("AccY", acceY);
//  newRow.setFloat("AccZ", acceZ);
//  newRow.setFloat("GyroX", gyroX);
//  newRow.setFloat("GyroY", gyroY);
//  newRow.setFloat("GyroZ", gyroZ);
//  newRow.setFloat("Yaw", yaw);
//  newRow.setFloat("Pitch", pitch);
//  newRow.setFloat("Roll", roll);
//  newRow.setFloat("Pressure", pressure);
//  newRow.setFloat("Alttitude", alttitude);
//  newRow.setFloat("Temperature", temperature);
  

//  readingCounter++;

//  if (readingCounter % numReadings ==0)
//  {
//    saveTable(table, "data/Avionics.csv");
//  }
//}
