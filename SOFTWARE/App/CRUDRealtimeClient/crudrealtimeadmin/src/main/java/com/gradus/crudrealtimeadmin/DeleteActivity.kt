package com.gradus.crudrealtimeadmin

import android.os.Bundle
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.FirebaseDatabase
import com.gradus.crudrealtimeadmin.databinding.ActivityDeleteBinding
import com.gradus.crudrealtimeadmin.databinding.ActivityUploadBinding

class DeleteActivity : AppCompatActivity() {
    private lateinit var binding: ActivityDeleteBinding
    private lateinit var databaseReference: DatabaseReference

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityDeleteBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.deleteButton.setOnClickListener {
            val userId = binding.deleteUsername.text.toString()
            if (userId.isNotEmpty())
                deleteData(userId)
            else
                Toast.makeText(this, "Ingrese un ID correcto", Toast.LENGTH_SHORT).show()
        }
    }

    private fun deleteData(userId: String) {
        databaseReference = FirebaseDatabase.getInstance().getReference("User Information")
        databaseReference.child(userId).removeValue().addOnSuccessListener {
            binding.deleteUsername.text.clear()
            Toast.makeText(this, "Eliminado", Toast.LENGTH_SHORT).show()
        }.addOnFailureListener {
            Toast.makeText(this, "No se ha podido eliminar", Toast.LENGTH_SHORT).show()
        }
    }
}