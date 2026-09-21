fetch("../json/overview.json")
  .then((Response) => Response.json())
  .then((data) => {
    document.getElementById("vehicleCount").textContent = data.vehicle_Id_Count;
    document.getElementById("vehicleType").textContent =
      data.vehicle_Type_Count;
    document.getElementById("streetCount").textContent = data.street_Count;
    document.getElementById("congestionCount").textContent =
      data.congested_Count;
    document.getElementById("uncongestionCount").textContent =
      data.uncongested_Count;
  });

// Read "street.json" and present top 10 streets having the most vehicles
// Then present other streets to select

fetch("../json/street.json")
  .then((Response) => Response.json())
  .then((data) => {
    // Sort vehicle count on each street in descending order

    data.sort((a, b) => b.vehicleCount - a.vehicleCount);

    // Take top 10 street have most vehicles

    const top10 = data.slice(0, 10);

    const tableBody = document.getElementById("topStreets");

    top10.forEach((street, index) => {
      const row = `
        <tr>
          <td>${street.streetName}</td>
          <td>${street.vehicleCount}</td>
        </tr>
        `;
      tableBody.innerHTML += row;
    });

    // Select other street and see number of vehicle

    const others = data.slice(10, 75);

    const selection = document.getElementById("otherStreets");
    const vehicleCount = document.getElementById("otherVehicleCount");

    others.forEach((street, index) => {
      const option = `
      <option>${street.streetName}</option>
      `;
      selection.innerHTML += option;
    });

    selection.addEventListener("change", () => {
      const selectedStreet = others.find(
        (street) => street.streetName === selection.value,
      );
      vehicleCount.textContent = selectedStreet.vehicleCount;
    });

    // Sort congested count in descending order

    data.sort((a, b) => b.congestedCount - a.congestedCount);

    // Take top 10 street have most congested occurences

    const top10CongestedStreet = data.slice(0, 10);

    const topCongestions = document.getElementById("topCongestions");

    top10CongestedStreet.forEach((street, index) => {
      const row = `
      <tr>
        <td>${street.streetName}</td>
        <td>${street.congestedCount}</td>
      </tr>
      `;
      topCongestions.innerHTML += row;
    });

    // Select other street & see number of congested occurences

    const otherCongestedStreet = data.slice(10, 75);

    const selectOtherCongestedStreet = document.getElementById(
      "otherCongestedStreet",
    );
    const otherStreetCongestedCount = document.getElementById(
      "otherStreetCongestedCount",
    );

    otherCongestedStreet.forEach((street, index) => {
      const option = `
      <option>${street.streetName}</option>
      `;
      selectOtherCongestedStreet.innerHTML += option;
    });

    selectOtherCongestedStreet.addEventListener("change", () => {
      const selectedStreet = otherCongestedStreet.find(
        (street) => street.streetName === selectOtherCongestedStreet.value,
      );
      otherStreetCongestedCount.textContent = selectedStreet.congestedCount;
    });
  });
