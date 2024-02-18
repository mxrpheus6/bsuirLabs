package com.lab1.CurrencyConverter.repo;

import com.lab1.CurrencyConverter.entity.CurrencyConverterEntity;
import org.springframework.data.repository.CrudRepository;

public interface CurrencyConverterRepository extends CrudRepository <CurrencyConverterEntity, Long> {
}
