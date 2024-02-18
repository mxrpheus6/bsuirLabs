package com.lab1.CurrencyConverter.controller;

import com.lab1.CurrencyConverter.entity.CurrencyConverterEntity;
import com.lab1.CurrencyConverter.repo.CurrencyConverterRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import static com.lab1.CurrencyConverter.service.CurrencyConverterService.convertCurrency;

@RestController
public class CurrencyConverterController {

    @Autowired
    private CurrencyConverterRepository currencyConverterRepository;

    public static class ConvertRestResponse {
        private String fromCurrency;
        private double amount;
        private String toCurrency;
        private double convertedAmount;

        public String getFromCurrency() {
            return fromCurrency;
        }

        public void setFromCurrency(String fromCurrency) {
            this.fromCurrency = fromCurrency;
        }

        public double getAmount() {
            return amount;
        }

        public void setAmount(double amount) {
            this.amount = amount;
        }

        public String getToCurrency() {
            return toCurrency;
        }

        public void setToCurrency(String toCurrency) {
            this.toCurrency = toCurrency;
        }

        public double getConvertedAmount() {
            return convertedAmount;
        }

        public void setConvertedAmount(double convertedAmount) {
            this.convertedAmount = convertedAmount;
        }
    }

    @GetMapping("/conversion")
    public ConvertRestResponse restConvert(@RequestParam String fromCurrency,
                                           @RequestParam double amount,
                                           @RequestParam String toCurrency) {
        ConvertRestResponse result = new ConvertRestResponse();
        result.setFromCurrency(fromCurrency.toUpperCase());
        result.setAmount(amount);
        result.setToCurrency(toCurrency.toUpperCase());
        result.setConvertedAmount(convertCurrency(fromCurrency, amount, toCurrency));

        saveToDatabase(result);

        return result;
    }

    private void saveToDatabase(ConvertRestResponse response) {
        CurrencyConverterEntity entity = new CurrencyConverterEntity();
        entity.setFromCurrency(response.getFromCurrency());
        entity.setAmount(response.getAmount());
        entity.setToCurrency(response.getToCurrency());
        entity.setConvertedAmount(response.getConvertedAmount());

        currencyConverterRepository.save(entity);
    }
}
