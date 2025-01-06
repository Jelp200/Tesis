package com.gradus.crudrealtimeadmin

import android.os.Bundle
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.FirebaseDatabase
import com.gradus.crudrealtimeadmin.databinding.ActivityUpdateBinding
import com.gradus.crudrealtimeadmin.databinding.ActivityUploadBinding
import java.util.Date

class UpdateActivity : AppCompatActivity() {
    private lateinit var binding: ActivityUpdateBinding
    private lateinit var databaseReference: DatabaseReference

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityUpdateBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.updateButton.setOnClickListener {
            val referenceUsername = binding.referenceUsername.text.toString()
            val updateUsername = binding.updateUsername.text.toString()
            val updateSector = binding.updateSector.text.toString()
            val updateBirthDate = binding.updateBirthDate.text.toString()

            updateData(referenceUsername, updateUsername, updateSector, updateBirthDate)
        }
    }

    private fun updateData(userId: String, userName: String, sectorName: String, birthDate: String) {
        databaseReference = FirebaseDatabase.getInstance().getReference("User Information")
        val userData = mapOf<String, String>("userName" to userName, "sectorName" to sectorName, "birthDate" to birthDate)
        databaseReference.child(userId).updateChildren(userData).addOnSuccessListener {
            binding.referenceUsername.text.clear()
            binding.updateUsername.text.clear()
            binding.updateSector.text.clear()
            binding.updateBirthDate.text.clear()
            Toast.makeText(this, "Actualizado", Toast.LENGTH_SHORT).show()
        }.addOnFailureListener {
            Toast.makeText(this, "No se ha podido actualizar", Toast.LENGTH_SHORT).show()
        }
    }
}