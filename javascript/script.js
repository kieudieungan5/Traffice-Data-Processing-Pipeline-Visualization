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

// Read "street.json" and present top 10 streets having the most vehicle records
// Then can choose other street

fetch("../json/street.json")
  .then((Response) => Response.json())
  .then((data) => {
    // Sort vehicle records on each street in descending order

    data.sort((a, b) => b.vehicleRecord - a.vehicleRecord);

    // Take top 10 street have most vehicles

    const top10 = data.slice(0, 10);

    const tableBody = document.getElementById("topStreets");

    top10.forEach((street, index) => {
      const row = `
        <tr>
          <td>${street.streetName}</td>
          <td>${street.vehicleRecord}</td>
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
      vehicleCount.textContent = selectedStreet.vehicleRecord;
    });

    // Sort congested records on each street in descending order

    data.sort((a, b) => b.congestedRecord - a.congestedRecord);

    // Take top 10 street have most congested occurences

    const top10CongestedStreet = data.slice(0, 10);

    const topCongestions = document.getElementById("topCongestions");

    top10CongestedStreet.forEach((street, index) => {
      const row = `
      <tr>
        <td>${street.streetName}</td>
        <td>${street.congestedRecord}</td>
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
      otherStreetCongestedCount.textContent = selectedStreet.congestedRecord;
    });

    // Sort congestion rate on each street in descending order
    // data.sort((a, b) => b.congestionRate - a.congestionRate);

    // Take top 10 streets have the highest congestion rate

    // const top10CongestionRate = data.slice(0, 10);

    // const topCongestionRate = document.getElementById("abnomalStreet");

    // top10CongestionRate.forEach((street, index) => {
    //   const row = `
    //   <tr>
    //     <td>${street.streetName}</td>
    //     <td>${street.vehicleRecord}</td>
    //     <td>${street.congestionRate}</td>
    //   </tr>
    //   `;
    //   topCongestionRate.innerHTML += row;
    // });
  });

// Read median.json
fetch("../json/median.json")
  .then((Response) => Response.json())
  .then((data) => {
    document.getElementById("medianVehicleRecord").textContent =
      data.median_Vehicle_Record;
    document.getElementById("medianCongestionRateValue").textContent =
      data.median_Congestion_Rate;
  });

// Read anomaly.json
fetch("../json/anomaly.json")
  .then((Response) => Response.json())
  .then((data) => {
    // Sort congestion rate on each street in descending order
    data.sort((a, b) => b.congestionRate - a.congestionRate);

    const anomalStreets = document.getElementById("abnomalStreet");

    data.forEach((street, index) => {
      const row = `
      <tr>
        <td>${street.streetName}</td>
        <td>${street.vehicleRecord}</td>
        <td>${street.congestionRate}</td>
      </tr>
      `;
      anomalStreets.innerHTML += row;
    });
  });
