<template>
  <div class="row justify-content-center">
    <div class="container-fluid" >
    <div class="row">
    <div class="col-4">
      <table class="table align-left">
  <thead>
    <tr>
      <th scope="col">#</th>
      <th scope="col">Video Name</th>
      <th scope="col">Select</th>
      <th scope="col">Delete</th>
    </tr>
  </thead>
  <tbody>
    <tr v-for="(video, index) in videos" :key="video.videoName">
      <th scope="row">{{index+1}}</th>
      <td class='tdVideoName'>{{video.videoName}}</td>
      <td><button type="button" class="btn btn-primary" @click="updateVideoLoc(video.videoLocation)">Select</button></td>
      <td><button type="button" class="btn btn-danger" @click="updateVideoLoc(video.videoLocation)">Delete</button></td>
    </tr>
  </tbody>
</table>
    </div>
    <div class="col-8">

      <video
      :key="currentVideo"
      width="720"
      controls
    >
      <source
        :src="currentVideo"
        type="video/mp4"
      >
    </video>
    </div>
  <div class="col-4"></div>
  <div class="col-8">
    <div id="carouselExampleIndicators" class="carousel slide" data-bs-ride="carousel">
  <div class="carousel-indicators">
    <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="0" class="active" aria-current="true" aria-label="Slide 1"></button>
    <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="1" aria-label="Slide 2"></button>
    <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="2" aria-label="Slide 3"></button>
  </div>
    </div>
  <div class="carousel-inner">
    <div class="carousel-item active">
      <img src="C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture1.jpg" class="d-block w-50" alt="...">
    </div>
    <div class="carousel-item">
      <img src="C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture2.jpg" class="d-block w-50" alt="...">
    </div>
    <div class="carousel-item">
      <img src="C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture3.jpg" class="d-block w-50" alt="...">
    </div>
  </div>
  <button class="carousel-control-prev" type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide="prev">
    <span class="carousel-control-prev-icon" aria-hidden="true"></span>
    <span class="visually-hidden">Previous</span>
  </button>
  <button class="carousel-control-next" type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide="next">
    <span class="carousel-control-next-icon" aria-hidden="true"></span>
    <span class="visually-hidden">Next</span>
  </button>
</div>
    </div>
    <div>
    </div>
    </div>
  </div>
</template>
<script>
export default {
data() {
        return {
            currentVideo: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/hiveVideos/Angry_Cat.mov',
            videos: [
              {
                videoName: 'Timestamp: 4/1/2022 17:58:00',
                videoLocation: '@/assets/hiveVideos/Drone32657.mp4',
                alertedImages: [ 
                  'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture1.jpg',
                  'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture2.jpg',
                  'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture3.jpg'
                ]
              },
              {
                videoName: 'Broken Link',
                videoLocation: '@/assets/hiveVideos/Drone32657.mp4'
              },
              {
                videoName: 'Funny-Drone-Video',
                videoLocation: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/hiveVideos/DRONE.mp4'
              },
              {
                videoName: 'Angry Cat Video',
                videoLocation: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/hiveVideos/Angry_Cat.mov'
              },
            ]
        }
    },
    methods: {
      updateVideoLoc(videoLocation){
        console.log(videoLocation)
        this.currentVideo = videoLocation
      }
    },
    computed: {
      source() {
      return this.currentVideo
      }
    }
}
</script>
<style scoped>
.tdVideoName{
  text-align: left;
}
</style>