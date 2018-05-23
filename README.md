# Aid-Management-System
When disaster hits a populated area, the most critical task is to provide immediately affected people with what they need as quickly and as efficiently as possible.
This project completes an application that manages the list of goods that need to be shipped to the disaster area. The client application tracks the quantity of items needed, tracks the quantity on hand, and stores the information in a file for future use. 
The types of goods that need to be shipped are of two categories; 
•	Non-Perishable products, such as blankets and tents, which have no expiry date. We refer to products in this category as Product objects.
•	Perishable products, such as food and medicine, that have an expiry date. We refer to products in this category as Perishable. 


OVERVIEW OF THE CLASSES TO BE DEVELOPED

The classes used by the client application are:
Date	
A class to be used to hold the expiry date of the perishable items.
ErrorState	
A class to keep track of the error state of client code. Errors may occur during data entry and user interaction.
Product	
A class for managing non-perishable products.
Perishable	
A class for managing perishable products. This class inherits the structure of the “Product” class and manages an expiry date.
iProduct	
An interface to the Product hierarchy. This interface exposes the features of the hierarchy available to the client application. Any “iProduct” class can
•	read itself from or write itself to the console
•	save itself to or load itself from a text file
•	compare itself to a unique C-string identifier
•	determine if it is greater than another product in the collating sequence  
•	report the total cost of the items on hand
•	describe itself
•	update the quantity of the items on hand
•	report its quantity of the items on hand
•	report the quantity of items needed
•	accept a number of items
Using this class, the client application can 
•	save its set of iProducts to a file and retrieve that set later
•	read individual item specifications from the keyboard and display them on the screen
•	update information regarding the number of each product on hand 

THE CLIENT APPLICATION

The client application manages the iProducts and provides the user with options to 
•	list the Products
•	display details of a Product
•	add a Product
•	add items of a Product
•	update the items of a Product
•	delete a Product
•	sort the set of Products
