vNineFeed Web API
=================

Event Level Data Requests
-------------------------

| As a vNine customer, a URL will be provided to you. That URL can be entered into any browser or used by an application to retrieve raw market data.

| In order to retrieve the desired market data, you can make a request to:
| "https://{address}/V1/Export/{exchangeName}/{symbol}?date={sessionDate}?events={eventType}?timebias={timeBias}"

| address: The base URL you will be provided with to obtain symbol information from Vertex Analytics servers

| exchangeName: The exchange name of the contract

.. note:: There are two exchanges available: ( CME, ICE )

| symbol:  The symbol of the desired contract

.. note:: To force an explicit choice, add the month and year code. If no choice is made the API will default to the front month on the selected date. Using the notion [1] will retrieve data from the back contract for the selected date. For example ES[1] on 2018/02/02 will retrieve from the ESM8 contract

| sessionDate: The date of the session

.. note:: The date should be formatted as: yyyymmdd

| eventType: The type of query that will run

.. note:: There are two types of queries available: ( all, tradesOnly )

| timeBias:  How much to offset UTC Timestamp

.. note:: This is an optional field and does not need to be in the request. If it is left off the default (UTC) will be used

.. note:: Can be + or - before the number and for every hour add 60

Ex.::

	https://***********/V1/Export/CME/ESH8?date=20180228&events=all&user=YourName

Additionally, you must supply an access token in the header.

Ex.::

	Authorization: Bearer VlhBMEMxMjBGRDY4Q0I1NDU4RS5BNUFCNUM2QzlTLjAwMEJEMDBEQjAxMEIwMDE4

See the VertexUserServicer.cs class or request the User Server REST API document.

.. note:: A script to pull multiple days of data for a contract must only use one query type per date range and have a rest after each request of 500 milliseconds. For example, if you'd like a month's worth of data for both 'all' and 'tradesOnly' for a contract, first, run a script to get all events for the date range. Once that has completed, run a script to get all trades data. Although, before you begin running your script for proper use, we recommend setting up a time with us to perform a test run of it so that we can monitor everything and make sure it is running optimally.

End of Session (EOS) data Requests
-----------------------------------

| There is a different format to the URL when requesting EOS data. 

| The events parameter is removed, and the date parameter is changed to allow users to request a date range:
| https://{address}/V1/EOS/{exchangeName}/{symbol}?startdate={startDate}&enddate={endDate}

| Again, you must additionally supply an access token in the header.

Ex.::

	Authorization: Bearer VlhBMEMxMjBGRDY4Q0I1NDU4RS5BNUFCNUM2QzlTLjAwMEJEMDBEQjAxMEIwMDE4

See the VertexUserServicer.cs class or request the User Server REST API document.

JSON Response
-------------

Once the parameters are set and the URL is executed against the real Vertex API, a JSON response is provided:

| {
|		"ExportStatus" : {
|		"symbol" : "ES",
|		"date" : 20180202,
|		"statusCode" : 4,
|		"statusText" : "Ready",
|		"completed" : true
|		"progress" : 13678259,
|		"total" : 13678259,
|		"fileName" : "ESH8_20180202_10_OptRec_Events_20180202",
|		"Url" : "https://***********/V1/Data/ESH8_20180202/ESH8_20180202_10_OptRec_Events_20180202.zip"
| }}

| As the request is being processed, the status code, progress count, and other fields reflect the current state of the request. 
| Continue to make the request to see updates until "completed" is true.

.. note:: If the request is successful, the status code will be 4, completed will be true, and the URL is provided to download the file. 
.. note:: If there is an error with the request, the status code is not 4 but completed will still be true. A good coding practice is to time out the client if the progress byte count is not incrementing after a certain amount of time.

| You should use the statusText for display purposes, as the specific wording of the text in statusText may change in the future.
| Use statusCode for programming state management.