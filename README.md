# CurrencyConverter
A Real Time Currency Converter using Exchange Rate API.

#Motive
This project aims to make me learn the basics of using APIs to make programs that make use of real time facts and stats. This would help me analyze data and comment upon the factual nature of things through programming. I hope to make use of it in the future when I will be working in Machine Learning and Cloud Computing.

#Resources
I used the C++ Rest SDK for using http_client.h library to send API request to the client.
The Client I used is https://apilayer.com/marketplace/exchangerates_data-api for this project's API, although it only allows 100 requests per month and I have already used 10 of those during debugging.

#TheWayItWorks
So this program utilises 3 aspects,
1. The amount to convert
2. The currency from where to convert.
3. The currency to which to convert.
It takes these from the user and makes an HTTP request using the values as parameters to send it to the Client API. Then it handles the JSON reponse for the output.
STEPS:
1. Takes Values from the user.
2. Setup HTTP request and execution by defining the Client and building the URI for the specific API endpoint.
3. Builds Query parameters by appending the values and the API key of the developer.
4. The Asynchronous HTTP request is the sent.
     1. The First Lambda handles the HTTP response upon status code 200 OK. If so, it extracts the JSON body.
     2. The Second Lambda handles the JSON response which extracts the Rate from JSON object and prints it.
5. The Do-While Loop then asks for another try... (My Request limit drainage (T_T) ).

#Problems
Although it sounds cool, there are certain problems over here
1. Firstly, the API key is there for all to see... no security, if this would have been an official project for a big company, I would be ded.
2. The Do-While loop consumes time and space. Its very slow on the first request and the Complexity is out of roof. Not an efficient code.
3. It could have more cool features like historical exchange rates or the lastest value according to the time, but I have yet to learn alot of complex things so I guess this was a good start.

#Enjoy
This was fun. and cool. and I hope I make more of these types in future. Peace!

