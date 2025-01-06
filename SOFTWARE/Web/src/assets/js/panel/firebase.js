// Import de funciones requeridas para el SDKs
import { initializeApp } from "https://www.gstatic.com/firebasejs/11.1.0/firebase-app.js";
import { getDatabase, set, get, update, remove, ref, child }
from "https://www.gstatic.com/firebasejs/11.1.0/firebase-database.js";

// Configuración de la app web con firebase
const firebaseConfig = {
    apiKey: "AIzaSyAhxUdv7wiSgw2P16FnAkWTirPgJw3sNYE",
    authDomain: "crud-realtime-client-396d7.firebaseapp.com",
    databaseURL: "https://crud-realtime-client-396d7-default-rtdb.firebaseio.com",
    projectId: "crud-realtime-client-396d7",
    storageBucket: "crud-realtime-client-396d7.firebasestorage.app",
    messagingSenderId: "593254884908",
    appId: "1:593254884908:web:4ee92625f9050b42031389"
};

// Inicialización de Firebase
const app = initializeApp(firebaseConfig);
const db = getDatabase(app);

// Elementos DOM
const userName = document.querySelector("#userName");
const birthDate = document.querySelector("#birthDate");
const sectorName = document.querySelector("#sectorName");
const userId = document.querySelector("#userId");
const searchIdNumber = document.querySelector("#searchIdNumber");
const readUsername = document.querySelector("#readUsername");
const readSector = document.querySelector("#readSector");
const readBirth = document.querySelector("#readBirth");

const saveButton = document.querySelector("#saveButton");
const updateButton = document.querySelector("#updateButton");
const deleteButton = document.querySelector("#deleteButton");
const searchButton = document.querySelector("#searchButton");

export function UploadData() {
    set(ref(db, "User Information/" + userId.value), {
        userName: userName.value,
        birthDate: birthDate.value,
        sectorName: sectorName.value,
        userId: userId.value
    })
    .then(() => {
        alert("Los datos han sido ingresados");
    })
    .catch((error) => {
        alert(error);
    });
}

export function UpdateData() {
    update(ref(db, "User Information/" + userId.value), {
        userName: userName.value,
        birthDate: birthDate.value,
        sectorName: sectorName.value
    })
    .then(() => {
        alert("Los datos han sido actualizados");
    })
    .catch((error) => {
        alert(error);
    });
}

export function DeleteData() {
    remove(ref(db, "User Information/" + userId.value))
    .then(() => {
        alert("Los datos han sido eliminados");
    })
    .catch((error) => {
        alert(error);
    });
}

export function SearchData() {
    const dbRef = ref(db);
    get(child(dbRef, "User Information/" + searchIdNumber.value))
    .then((snapshot) => {
        if (snapshot.exists()) {
            readUsername.textContent = snapshot.val().userName;
            readSector.textContent = snapshot.val().sectorName;
            readBirth.textContent = snapshot.val().birthDate;
        } else {
            alert("No se encontraron datos.");
        }
    })
    .catch((error) => {
        alert(error);
    });
}

// Event Listeners
saveButton.addEventListener('click', UploadData);
updateButton.addEventListener('click', UpdateData);
deleteButton.addEventListener('click', DeleteData);
searchButton.addEventListener('click', SearchData);