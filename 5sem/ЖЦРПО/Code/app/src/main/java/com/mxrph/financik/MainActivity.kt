package com.mxrph.financik

import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.DividerItemDecoration
import androidx.recyclerview.widget.LinearLayoutManager
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.firestore.FirebaseFirestore
import com.mxrph.financik.adapter.Transaction
import com.mxrph.financik.adapter.TransactionAdapter
import com.mxrph.financik.databinding.ActivityMainBinding
import java.text.SimpleDateFormat
import java.util.Calendar
import java.util.Date
import java.util.Locale

class MainActivity : AppCompatActivity() {
    private lateinit var binding: ActivityMainBinding
    private lateinit var auth: FirebaseAuth
    private lateinit var db: FirebaseFirestore

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        setCurrentDate()

        db = FirebaseFirestore.getInstance()
        auth = FirebaseAuth.getInstance()

        setupBalanceListener()
        loadDailyIncomeAndExpenses()
        loadDailyTransactions()

        binding.addCategoryButton.setOnClickListener {
            startActivity(Intent(this, AddCategoryActivity::class.java))
        }

        binding.addTransactionButton.setOnClickListener {
            startActivity(Intent(this, AddTransactionActivity::class.java))
        }

        binding.editBalanceButton.setOnClickListener {
            startActivity(Intent(this, EditBalanceActivity::class.java))
        }

        binding.historyButton.setOnClickListener {
            startActivity(Intent(this, HistoryActivity::class.java))
        }

        binding.settingsButton.setOnClickListener {
            startActivity(Intent(this, SettingsActivity::class.java))
        }
    }

    private fun setCurrentDate() {
        val dateFormat = SimpleDateFormat("dd MMMM, yyyy", Locale.getDefault())
        val currentDate = dateFormat.format(Date())
        binding.calendarView.text = currentDate
    }

    private fun setupBalanceListener() {
        val userId = auth.currentUser?.uid
        if (userId != null) {
            val userDocRef = db.collection("users").document(userId)
            userDocRef.addSnapshotListener { snapshot, e ->
                if (e != null) {
                    Toast.makeText(this, "Error loading balance", Toast.LENGTH_SHORT).show()
                    return@addSnapshotListener
                }

                if (snapshot != null && snapshot.exists()) {
                    val balance = snapshot.getDouble("balance") ?: 0.0
                    binding.balanceAmount.text = String.format("$%.2f", balance)
                }
            }
        } else {
            Toast.makeText(this, "User not authorized", Toast.LENGTH_SHORT).show()
        }
    }

    private fun loadDailyIncomeAndExpenses() {
        val preferences = getSharedPreferences("financik_prefs", MODE_PRIVATE)

        val cachedIncome = preferences.getFloat("daily_income", 0.0f)
        val cachedExpenses = preferences.getFloat("daily_expenses", 0.0f)

        binding.incomeAmount.text = String.format("$%.2f", cachedIncome)
        binding.expensesAmount.text = String.format("$%.2f", cachedExpenses)

        val userId = auth.currentUser?.uid
        if (userId == null) {
            Toast.makeText(this, "User not authorized", Toast.LENGTH_SHORT).show()
            return
        }

        val today = SimpleDateFormat("dd/MM/yyyy", Locale.getDefault()).format(Calendar.getInstance().time)
        val userTransactionsRef = db.collection("users").document(userId).collection("transactions")

        userTransactionsRef
            .whereEqualTo("type", "Income")
            .whereEqualTo("date", today)
            .get()
            .addOnSuccessListener { documents ->
                var totalIncome = 0.0
                for (document in documents) {
                    totalIncome += document.getDouble("amount") ?: 0.0
                }
                binding.incomeAmount.text = String.format("$%.2f", totalIncome)

                preferences.edit().putFloat("daily_income", totalIncome.toFloat()).apply()
            }
            .addOnFailureListener {
                Toast.makeText(this, "Error loading income", Toast.LENGTH_SHORT).show()
            }

        userTransactionsRef
            .whereEqualTo("type", "Expense")
            .whereEqualTo("date", today)
            .get()
            .addOnSuccessListener { documents ->
                var totalExpenses = 0.0
                for (document in documents) {
                    totalExpenses += document.getDouble("amount") ?: 0.0
                }
                binding.expensesAmount.text = String.format("$%.2f", totalExpenses)

                preferences.edit().putFloat("daily_expenses", totalExpenses.toFloat()).apply()
            }
            .addOnFailureListener {
                Toast.makeText(this, "Error loading expenses", Toast.LENGTH_SHORT).show()
            }
    }

    private fun loadDailyTransactions() {
        val userId = auth.currentUser?.uid
        if (userId == null) {
            Toast.makeText(this, "User not authorized", Toast.LENGTH_SHORT).show()
            return
        }

        val today = SimpleDateFormat("dd/MM/yyyy", Locale.getDefault()).format(Calendar.getInstance().time)
        val userTransactionsRef = db.collection("users").document(userId).collection("transactions")

        userTransactionsRef
            .whereEqualTo("date", today)
            .orderBy("timestamp", com.google.firebase.firestore.Query.Direction.DESCENDING)
            .get()
            .addOnSuccessListener { documents ->
                val transactions = mutableListOf<Transaction>()
                var totalAmount = 0.0

                for (document in documents) {
                    val id = document.getString("id") ?: "Unknown"
                    val type = document.getString("type") ?: "Unknown"
                    val name = document.getString("title") ?: "Unnamed"
                    val category = document.getString("category") ?: "No category"
                    val amount = document.getDouble("amount") ?: 0.0

                    transactions.add(Transaction(id, type, name, category, amount))
                    totalAmount += if (type == "Income") amount else -amount
                }

                val adapter = TransactionAdapter(transactions)  { transaction ->
                    showDeleteConfirmationDialog(transaction)
                }

                binding.transactionHistoryRecyclerView.layoutManager = LinearLayoutManager(this)
                binding.transactionHistoryRecyclerView.adapter = adapter

                val itemDecoration = DividerItemDecoration(this, DividerItemDecoration.VERTICAL)
                itemDecoration.setDrawable(ContextCompat.getDrawable(this, R.drawable.divider)!!)
                binding.transactionHistoryRecyclerView.addItemDecoration(itemDecoration)
            }
            .addOnFailureListener {
                Toast.makeText(this, "Error loading transactions", Toast.LENGTH_SHORT).show()
            }
    }

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

                        loadDailyTransactions()
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