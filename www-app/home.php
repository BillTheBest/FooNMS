<?php
require_once("includes/user-management.inc");

session_start();
redirectIfNotLoggedIn();

	//The rest of the page.
	echo "Logged in as ".$_SESSION['username'];
	echo "<a href=\"./logout.php\">Logout</a>";



?>