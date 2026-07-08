package com.mxrph.financik

import android.os.Bundle
import android.util.Log
import android.widget.Toast
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.DividerItemDecoration
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.google.android.material.button.MaterialButton
import com.google.android.material.datepicker.MaterialDatePicker
import com.google.android.material.textview.MaterialTextView
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.firestore.FirebaseFirestore
import com.mxrph.financik.adapter.Transaction
import com.mxrph.financik.adapter.TransactionAdapter
import com.mxrph.financik.databinding.ActivityHistoryBinding
import java.text.SimpleDateFormat
import java.util.Calendar
import java.util.Locale
import kotlin.math.round

class HistoryActivity : AppCompatActivity() {
    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }

    external fun isDateInMonth(date: String, selectedDay: Int, selectedMonth: Int, selectedYear: Int): Boolean

    private lateinit var binding: ActivityHistoryBinding

    private lateinit var auth: FirebaseAuth
    private lateinit var db: FirebaseFirestore
    private lateinit var monthTextView: MaterialTextView
    private lateinit var transactionRecyclerView: RecyclerView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityHistoryBinding.inflate(layoutInflater)
        setContentView(binding.root)

        db = FirebaseFirestore.getInstance()
        auth = FirebaseAuth.getInstance()

        monthTextView = findViewById(R.id.monthTextView)
        transactionRecyclerView = findViewById(R.id.transactionRecyclerView)

        setCurrentMonth()

        val selectMonthButton: MaterialButton = findViewById(R.id.selectMonthButton)
        selectMonthButton.setOnClickListener { showDatePicker() }
    }

    private fun setCurrentMonth() {
        val calendar = Calendar.getInstance()
        val month = calendar.get(Calendar.MONTH)
        val year = calendar.get(Calendar.YEAR)

        val monthName = calendar.getDisplayName(Calendar.MONTH, Calendar.LONG, Locale.getDefault())
        monthTextView.text = "$monthName\n$year"

        loadMonthlyTransactions(month, year)
    }
    private fun showDatePicker() {
        val datePicker = MaterialDatePicker.Builder.datePicker()
            .setTitleText("Select Date")
            .setSelection(MaterialDatePicker.todayInUtcMilliseconds())
            .build()

        datePicker.addOnPositiveButtonClickListener { selection ->
            val selectedDate = Calendar.getInstance().apply {
                timeInMillis = selection
            }

            val month = selectedDate.get(Calendar.MONTH)
            val year = selectedDate.get(Calendar.YEAR)
            val monthName = selectedDate.getDisplayName(Calendar.MONTH, Calendar.LONG, Locale.getDefault())
            monthTextView.text = "$monthName\n$year"

            loadMonthlyTransactions(month, year)
        }

        datePicker.show(supportFragmentManager, "datePicker")
    }

    private fun loadMonthlyTransactions(selectedMonth: Int, selectedYear: Int) {
        val userId = auth.currentUser?.uid
        if (userId == null) {
            Toast.makeText(this, "User not authorized", Toast.LENGTH_SHORT).show()
            return
        }

        val calendarStart = Calendar.getInstance()
        calendarStart.set(selectedYear, selectedMonth, 1)

        val calendarEnd = Calendar.getInstance()
        calendarEnd.set(selectedYear, selectedMonth, calendarStart.getActualMaximum(Calendar.DAY_OF_MONTH)) // Конец месяца

        val dateFormat = SimpleDateFormat("dd/MM/yyyy", Locale.getDefault())
        val startDate = dateFormat.format(calendarStart.time)
        val endDate = dateFormat.format(calendarEnd.time)

        Log.i("LoadTransactions", "Fetching transactions from $startDate to $endDate")

        val userTransactionsRef = db.collection("users").document(userId).collection("transactions")
        userTransactionsRef
            .whereGreaterThanOrEqualTo("date", startDate)
            .whereLessThanOrEqualTo("date", endDate)
            .orderBy("timestamp", com.google.firebase.firestore.Query.Direction.DESCENDING)
            .get()
            .addOnSuccessListener { documents ->
                val transactions = mutableListOf<Transaction>()
                var totalIncome = 0.00
                var totalExpense = 0.00

                for (document in documents) {
                    val id = document.getString("id") ?: "Unknown"
                    val type = document.getString("type") ?: "Unknown"
                    val name = document.getString("title") ?: "Unnamed"
                    val category = document.getString("category") ?: "No category"
                    val amount = document.getDouble("amount") ?: 0.0
                    val date = document.getString("date") ?: ""

                    if (isDateInMonth(date, selectedDay = 1, selectedMonth, selectedYear)) {
                        transactions.add(Transaction(id, type, name, category, amount))
                        if (type == "Income") {
                            totalIncome += amount
                            totalIncome = round(totalIncome * 100) / 100
                        } else {
                            totalExpense += amount
                            totalExpense = round(totalExpense * 100) / 100
                        }
                    }
                }

                binding.total.text = "Total Income = $$totalIncome | Total Expenses = $$totalExpense"

                val adapter = TransactionAdapter(transactions) { transaction ->
                    showDeleteConfirmationDialog(transaction)
                }

                binding.transactionRecyclerView.layoutManager = LinearLayoutManager(this)
                binding.transactionRecyclerView.adapter = adapter

                val itemDecoration = DividerItemDecoration(this, DividerItemDecoration.VERTICAL)
                itemDecoration.setDrawable(ContextCompat.getDrawable(this, R.drawable.divider)!!)
                binding.transactionRecyclerView.addItemDecoration(itemDecoration)
            }
            .addOnFailureListener {
                Toast.makeText(this, "Error loading transactions", Toast.LENGTH_SHORT).show()
            }
    }

    /*private fun isDateInMonth(date: String, selectedDay: Int, selectedMonth: Int, selectedYear: Int): Boolean {
        val dateParts = date.split("/")
        if (dateParts.size != 3) return false

        val day = dateParts[0].toIntOrNull() ?: return false
        val month = dateParts[1].toIntOrNull()?.minus(1) ?: return false
        val year = dateParts[2].toIntOrNull() ?: return false

        return year == selectedYear && month == selectedMonth
    }*/


    private fun showDeleteConfirmationDialog(transaction: Transaction) {
        AlertDialog.Builder(this)
            .setTitle("Delete transaction")
            .setMessage("Are you sure about deleting this transaction?")
            .setPositiveButton("Yes") { _, _ ->

                deleteTransactionFromDatabase(transaction)
            }
            .setNegativeButton("No", null)
            .show()
    }

    private fun deleteTransactionFromDatabase(transaction: Transaction) {
        val userId = auth.currentUser?.uid

        if (userId != null) {
            if (transaction.id != null) {
                val transactionRef = db.collection("users")
                    .document(userId)
                    .collection("transactions")
                    .document(transaction.id)

                transactionRef.delete()
                    .addOnSuccessListener {
                        Toast.makeText(this, "Transaction deleted", Toast.LENGTH_SHORT).show()
                    }
                    .addOnFailureListener {
                        Toast.makeText(this, "Error deleting transaction", Toast.LENGTH_SHORT)
                            .show()
                    }
            } else {
                Toast.makeText(this, "Transaction ID not found", Toast.LENGTH_SHORT).show()
            }
        }
    }
}