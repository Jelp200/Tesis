package com.gradus.crudrealtimeclient

import android.os.Bundle
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.FirebaseDatabase
import com.gradus.crudrealtimeclient.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    private lateinit var binding: ActivityMainBinding
    private lateinit var databaseReference: DatabaseReference

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.searchButton.setOnClickListener {
            val searchId: String = binding.searchIdNumber.text.toString()
            if (searchId.isNotEmpty()) {
                readData(searchId)
            } else
                Toast.makeText(this, "Ingrese el ID del elemento", Toast.LENGTH_SHORT).show()
        }
    }

    private fun readData(userId: String) {
        databaseReference = FirebaseDatabase.getInstance().getReference("User Information")
        databaseReference.child(userId).get().addOnSuccessListener {
            if (it.exists()) {
                val userName = it.child("userName").value
                val birthDate = it.child("birthDate").value
                val sectorName = it.child("sectorName").value
                Toast.makeText(this, "Se encontraron resultados", Toast.LENGTH_SHORT).show()
                binding.searchIdNumber.text.clear()
                binding.readUsername.text = userName.toString()
                binding.readSector.text = sectorName.toString()
                binding.readBirth.text = birthDate.toString()
                //* IMPELEMENTAR BINDING PARA BPM
            } else
                Toast.makeText(this, "ID no encontrado", Toast.LENGTH_SHORT).show()
        } .addOnFailureListener {
            Toast.makeText(this, "Algo salio mal...", Toast.LENGTH_SHORT).show()
        }
    }
}