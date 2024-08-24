#include <iostream>
#include <string>
#include <cpprest/http_client.h>


using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

class Currency {
	string amount;
	string from;
	string to;
public:
	Currency(string amount, string from, string to) {
		this->amount = amount;
		this->from = from;
		this->to = to;
	}

	string getAmount() {
		return amount;
	}
	string getFrom() {
		return from;
	}
	string getTo() {
		return to;
	}
};


int main() {
	cout << "\t		Real Time Currency Converter" << endl;
	cout << "------------------------------------------------------------------" << endl;
	string amount;
	string from;
	string to;
	char opt;

	do {
		cout << "\tThe Amount: ";
		cin >> amount;
		cout << endl;
		cout << "\tCurrent Currency: ";
		cin >> from;
		cout << endl;
		cout << "\tConvert to: ";
		cin >> to;

		Currency currency(amount, from, to);
		http_client client(U("https://api.apilayer.com/exchangerates_data"));
		uri_builder builder(U("/convert"));

		builder.append_query(U("to"), utility::conversions::to_string_t(currency.getTo()));
		builder.append_query(U("from"), utility::conversions::to_string_t(currency.getFrom()));
		builder.append_query(U("amount"), utility::conversions::to_string_t(currency.getAmount()));
		builder.append_query(U("apikey"), U("ftfnuLP0hIuHU822KE4qMrA3dM2yqqmi"));

		http_request request(methods::GET);
		request.set_request_uri(builder.to_string());

		cout << endl;

		try {
			client.request(request).then([](http_response response) {
				if (response.status_code() == status_codes::OK) {
					return response.extract_json();
				}
				else {
					throw runtime_error("Failed to get a valid response from the server. Status code: " + to_string(response.status_code()));
				}
				}).then([&currency](web::json::value body) {
					try {
						auto rate = body[U("info")][U("rate")].as_double();

						double amount = stod(currency.getAmount());
						double convertedAmount = amount * rate;

						cout << "\tRate: " << rate << " " <<currency.getTo() <<endl;
						cout << "\tConverted Amount: " << convertedAmount << " " << currency.getTo() << endl;
					}
					catch (const json::json_exception& e) {
						cerr << "Error parsing JSON response: " << e.what() << endl;
					}
					}).wait();
		}
		catch (const exception& e) {
			cerr << "An error occurred: " << e.what() << endl;
		}

		cout << "\n\n";
		cout << "Do you want to try again? (y = Yes, n = No)" << endl;
		cin >> opt;
	} while (opt != 'n' || opt == 'y');
}
