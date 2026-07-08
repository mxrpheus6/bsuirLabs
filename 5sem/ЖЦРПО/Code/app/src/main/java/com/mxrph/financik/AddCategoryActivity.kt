package com.mxrph.financik

import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.firestore.FirebaseFirestore
import com.mxrph.financik.databinding.ActivityAddCategoryBinding

class AddCategoryActivity : AppCompatActivity() {
    private lateinit var binding: ActivityAddCategoryBinding
    private lateinit var db: FirebaseFirestore

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityAddCategoryBinding.inflate(layoutInflater)
        setContentView(binding.root)

        db = FirebaseFirestore.getInstance()

        binding.saveCategoryButton.setOnClickListener {
            val categoryName = binding.categoryNameEditText.text.toString()
            if (categoryName.isNotEmpty()) {
                saveCategory(categoryName)
            } else {
                Toast.makeText(this, "Enter category name", Toast.LENGTH_SHORT).show()
            }
        }
    }

    private fun saveCategory(name: String) {
        val userId = FirebaseAuth.getInstance().currentUser?.uid
        if (userId != null) {
            val category = hashMapOf("name" to name)
            db.collection("users").document(userId).collection("categories").add(category)
                .addOnSuccessListener {
                    Toast.makeText(this, "Category saved", Toast.LENGTH_SHORT).show()
                    finish()
                }
                .addOnFailureListener {
                    Toast.makeText(this, "Error saving category", Toast.LENGTH_SHORT).show()
                }
        } else {
            Toast.makeText(this, "User not authorized", Toast.LENGTH_SHORT).show()
        }
    }
}