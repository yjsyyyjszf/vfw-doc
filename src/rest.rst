vNineFeed Rest API
==================

Subscription Requests
---------------------

| Before making a data request, you must subscribe to a symbol and retrieve a unique symbol ID and user ID.
| Subscriptions, symbol IDs, and user IDs are active until the market closes.
| 
| To subscribe to a symbol, you can make a request to:
| https://v9restapi.vertex-analytics.com/betameta/v2/OPEN/{Symbol}/{username}

Symbol Formatting
-----------------

There are two different ways to format the symbol you want to subscribe to.

For explicit Future symbols, you can format their information like this::

	{MICCODE}:FUT:{UNDERLYING FUTURE}{MONTH CODE}{YEAR CODE}

Ex.::

	XCME:FUT:ESU9

And for option chains, you can format their information like this::

	{MICCODE}:OOF:{ASSET CODE}{MONTH CODE}{YEAR CODE}

Ex.::

	XCME:OOF:OZSN9

.. Note:: Subscribing to an option chain will return all the options in the chain along with the underlying future.

JSON Response
-------------

| {
|		"status": 0, // error code
|		"message": "", // error message
|		"symbol": "XCME:FUT:NQU9", // echo of subscribed symbol
|		"symbolId": 8, // Unique symbol ID
|		"userId": 1011, // Unique user ID
|		"records": 119308, // Current number of records available
|		"instruments": [}] // Instrument definitions
| }

Data Requests
-------------

| To request data for your symbol, simply make a request to:
| https://v9restapi.vertex-analytics.com/betafeed/v2/EVNT/{SymbolID}/{sequencNnumber}/{maximumRecords}/{userID}

| sequenceNumber: The sequence number for the first element of the query
| maximumRecords: Maximum number of records to retrieve

Ex.::

	https://v9restapi.vertex-analytics.com/betafeed/v2/EVNT/211/0/1000/1234
