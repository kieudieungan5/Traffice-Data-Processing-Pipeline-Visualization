function updateData() {
  fetch("/json/statistic.json")
    .then((Response) => Response.json())
    .then((data) => {
      document.getElementById("vehicleCount").textContent = data.vehicle_Id;
      document.getElementById("vehicleType").textContent = data.vehicle_Type;
      document.getElementById("streetName").textContent = data.street_Name;
      document.getElementById("congestionCount").textContent =
        data.is_Congested;
      document.getElementById("uncongestionCount").textContent =
        data.is_Not_Congested;
    });
}
updateData();
