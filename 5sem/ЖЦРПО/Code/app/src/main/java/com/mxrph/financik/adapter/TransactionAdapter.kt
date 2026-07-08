package com.mxrph.financik.adapter

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.mxrph.financik.R

data class Transaction(
    val id: String? = null,
    val type: String,
    val name: String,
    val category: String,
    val amount: Double
)

class TransactionAdapter(private val transactions: MutableList<Transaction>,
                         private val onDeleteTransaction: (Transaction) -> Unit
) : RecyclerView.Adapter<TransactionAdapter.TransactionViewHolder>() {

    inner class TransactionViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        val transactionType: TextView = itemView.findViewById(R.id.transactionType)
        val transactionName: TextView = itemView.findViewById(R.id.transactionName)
        val transactionCategory: TextView = itemView.findViewById(R.id.transactionCategory)
        val transactionAmount: TextView = itemView.findViewById(R.id.transactionAmount)
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): TransactionViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.item_transaction, parent, false)
        return TransactionViewHolder(view)
    }

    override fun onBindViewHolder(holder: TransactionViewHolder, position: Int) {
        val transaction = transactions[position]
        holder.transactionType.text = transaction.type
        holder.transactionName.text = transaction.name
        holder.transactionCategory.text = transaction.category
        holder.transactionAmount.text = String.format("$%.2f", transaction.amount)

        holder.transactionAmount.setTextColor(
            if (transaction.type == "Income") 0xCC008000.toInt() else 0xCCFF0000.toInt()
        )

        val backgroundColor = if (position % 2 == 0) 0xFFEFEFEF.toInt() else 0xFFFFFFFF.toInt()
        holder.itemView.setBackgroundColor(backgroundColor)

        holder.itemView.setOnLongClickListener {
            onDeleteTransaction(transaction)
            true
        }
    }

    override fun getItemCount(): Int {
        return transactions.size
    }
}