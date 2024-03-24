#include "Weather.h"

MY::WeatherForecast::Weather::Weather(float temp, std::string date, std::string description) {
	this->temp = temp;
	this->date = date;
	this->description = description;
}

std::string MY::WeatherForecast::Weather::Date() {
	return this->date;
}

std::string MY::WeatherForecast::Weather::Descr() {
	return "description: " + this->description;
}

float MY::WeatherForecast::Weather::Temp() {
	return this->temp;
}

MY::WeatherForecast::WeatherForecast(std::string city, std::string API) {
	httplib::Client cli("api.openweathermap.org");
	std::string req1 = "/data/2.5/weather";
	req1 += "?q=" + city;
	req1 += "&appid=" + API;
	std::string req2 = "/data/2.5/forecast";
	if (auto i = cli.Get(req1)) {
		nlohmann::json res1 = nlohmann::json::parse(i->body);
		req2 += "?lat=";
		req2 += to_string(res1["coord"]["lat"]);
		req2 += "&lon=";
		req2 += to_string(res1["coord"]["lon"]);
		req2 += "&appid=" + API;
		if (auto j = cli.Get(req2)) {
			nlohmann::json res2 = nlohmann::json::parse(j->body);
			float middleTemp;
			int cnt;
			for (int k = 0; k < 5; k++) {
				MY::WeatherForecast::Weather w(res2["list"][8 * k]["main"]["temp"] - 273.15, res2["list"][8 * k]["dt_txt"], res2["list"][8 * k]["weather"][0]["description"]);
				this->Forecast.push_back(w);
				this->MinTemp.push_back(res2["list"][8 * k]["main"]["temp_min"] - 273.15);
				this->MaxTemp.push_back(res2["list"][8 * k]["main"]["temp_max"] - 273.15);
				middleTemp = 0;
				cnt = 1;
				while (res2["list"][8 * k]["dt_txt"] == res2["list"][8 * k + cnt - 1]["dt_txt"]) {
					middleTemp += res2["list"][8 * k + cnt - 1]["main"]["temp"] - 273.15;
					cnt++;
				}
				this->MiddleTemp.push_back(middleTemp / cnt);
			}
		}
		else {
			std::cout << "uncorrect request!\n";
		}
	}
	else {
		std::cout << "request error\n";
	}
}

MY::WeatherForecast::Weather MY::WeatherForecast::operator[](int ind) {
	return Forecast[ind];
}

std::ostream& MY::operator<<(std::ostream& stream, const MY::WeatherForecast::Weather& w)
{
	return stream << w.date << ": " << w.temp << ", " << w.description;
}

float MY::WeatherForecast::Get_Min_Temp(int index) {
	return this->MinTemp[index];
}

float MY::WeatherForecast::Get_Max_Temp(int index) {
	return this->MaxTemp[index];
}

float MY::WeatherForecast::Get_Middle_Temp(int index) {
	return MiddleTemp[index];
}