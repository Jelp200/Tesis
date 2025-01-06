package com.gradus.crudrealtimeadmin

import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.FirebaseDatabase
import com.gradus.crudrealtimeadmin.databinding.ActivityMainBinding
import com.gradus.crudrealtimeadmin.databinding.ActivityUploadBinding
import java.lang.ref.Reference

class UploadActivity : AppCompatActivity() {
    private lateinit var binding: ActivityUploadBinding
    private lateinit var databaseReference: DatabaseReference

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityUploadBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.saveButton.setOnClickListener {
            val userName = binding.uploadUsername.text.toString()
            val birthDate = binding.uploadBirthDate.text.toString()
            val sectorName = binding.uploadSector.text.toString()
            val userId = binding.uploadUserID.text.toString()

            databaseReference = FirebaseDatabase.getInstance().getReference("User Information")
            val userData = UserData(userName, birthDate, sectorName, userId)
            databaseReference.child(userId).setValue(userData).addOnSuccessListener {
                binding.uploadUsername.text.clear()
                binding.uploadBirthDate.text.clear()
                binding.uploadSector.text.clear()
                binding.uploadUserID.text.clear()

                Toast.makeText(this, "Guardado", Toast.LENGTH_SHORT).show()
                val intent = Intent(this@UploadActivity, MainActivity::class.java)
                startActivity(intent)
                finish()
            }.addOnFailureListener {
                Toast.makeText(this, "Fallido", Toast.LENGTH_SHORT).show()
            }
        }
    }
}