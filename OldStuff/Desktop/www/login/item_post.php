<?php

    session_start();

      $servername = "localhost";
      $username = "root";
      $password = "";
      $dbname = "mini-ebay";

      // Create connection
      $conn = new mysqli($servername, $username, $password, $dbname);
      // Check connection
      if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
      } 
      $date = new DateTime()
      $sql = "insert into item (itemID,status,postTime,userID,description,buyPrice,minPrice) 
      values($_POST[itemid],'$_POST[status]','$_POST[userid]','$_POST[description]','$_POST[buyprice]','$_POST[minprice]')";

      if ($conn->query($sql) === TRUE) {
        echo "New record created successfully";
  
        // Set session variables
      } 
      else {
          echo "Error: " . $sql . "<br>" . $conn->error;
      }

      $conn->close();
      //header( 'Location: ../main.php' );
?>          