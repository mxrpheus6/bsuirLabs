package com.lab1.CurrencyConverter.service;

import com.lab1.CurrencyConverter.model.ConvertResponseModel;
import org.springframework.stereotype.Service;
import org.springframework.web.client.HttpClientErrorException;
import org.springframework.web.client.RestTemplate;

@Service
public class CurrencyConverterService {

    private static final String apiUrl = "https://v6.exchangerate-api.com/v6/d6d8a4004c4b9d619b477865";

    public static double convertCurrency(String fromCurrency, double amount, String toCurrency) {
        RestTemplate restTemplate = new RestTemplate();
        String fullApiUrl = apiUrl + "/pair/" + fromCurrency.toUpperCase() + "/" + toCurrency.toUpperCase() + "/" + amount;
        try {
            ConvertResponseModel response = restTemplate.getForObject(fullApiUrl, ConvertResponseModel.class);
            return response.getConversionResult();
        } catch (HttpClientErrorException.NotFound e) {
            throw new IllegalArgumentException("Pavel Kazachenko Corporation. Invalid currency code");
        } catch (Exception e) {
            e.printStackTrace();
            throw e;
        }
    }
}
