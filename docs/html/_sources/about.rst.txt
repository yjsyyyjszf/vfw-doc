About vNineFeed
===============

vNine
-----

vNine is a web application that provides users with completely customizable visualization of 
futures market data.

vNineFeed Web API
-----------------

vNine Export is a Windows applet that allows users to quickly export and download raw market data in 
both csv file and raw binary formats. It can be extremely beneficial for logging important findings 
in vNine.

Binary output
~~~~~~~~~~~~~~

Binary output can be downloaded using the vNineFeed Rest API.

CSV output
~~~~~~~~~~

CSV output can be downloaded using the Export feature in the vNine browser client or programmatically via the web
API.

The resulting output is in a .zip (compressed) file containing a .csv (comma separated values) text file
suitable for importing into Microsoft Excel, a text editor, or other commercial and proprietary tools. Many
files contain more records than the maximum that Excel can open, so we recommend using a program
like TextPad or Visual Studio rather than using Excel.
The latest trade session's data becomes available through the API approximately 1 hour after session
close, depending on volume.

Troubleshooting
---------------

If you have any questions, please contact customer support at support@vertex-analytics.com.

Many customers choose to download the data using the vNine client, either manually or through scripts.
However, sample C# source code is available for those that prefer a programmatic solution. 

The sample code contains a variety of classes for performing the following operations:

- Authentication (login to get access token and logout to dispose of token)
- Downloading (download export files from Vertex. Supports a background thread)
- Reading (reads .csv and .zip files into event objects. Also supports background threads)
- Processing (checks and associates event objects, such as the lifetime of a quote)
