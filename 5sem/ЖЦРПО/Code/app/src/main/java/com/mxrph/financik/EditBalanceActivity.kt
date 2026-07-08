package com.mxrph.financik

import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.firestore.FirebaseFirestore

class EditBalanceActivity : AppCompatActivity() {

    private lateinit var balanceEditText: EditText
    private lateinit var confirmButton: Button
    private lateinit var auth: FirebaseAuth
    private lateinit var db: FirebaseFirestore

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_edit_balance)

        balanceEditText = findViewById(R.id.balanceEditText)
        confirmButton = findViewById(R.id.confirmButton)

        auth = FirebaseAuth.getInstance()
        db = FirebaseFirestore.getInstance()

        confirmButton.setOnClickListener {
            val newBalance = balanceEditText.text.toString()
            if (newBalance.isNotEmpty()) {
                updateBalance(newBalance.toDouble())
            } else {
                Toast.makeText(this, "Please enter a valid balance", Toast.LENGTH_SHORT).show()
            }
        }
    }

    private fun updateBalance(newBalance: Double) {
        val userId = auth.currentUser?.uid
        if (userId != null) {
            val userDocRef = db.collection("users").document(userId)
            userDocRef.update("balance", newBalance)
                .addOnSuccessListener {
                    Toast.makeText(this, "Balance updated successfully", Toast.LENGTH_SHORT).show()
                    finish()
                }
                .addOnFailureListener { e ->
                    Toast.makeText(this, "Error updating balance: ${e.message}", Toast.LENGTH_SHORT).show()
                }
        } else {
            Toast.makeText(this, "User not authorized", Toast.LENGTH_SHORT).show()
        }
    }
}