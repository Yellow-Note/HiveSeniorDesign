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
            <tr v-for="(video, index) in mediaStore.videos" :key="video.timestamp">
              <th scope="row">{{index+1}}</th>
              <td class='tdVideoName'>{{video.timestamp}}</td>
              <td><button type="button" class="btn btn-primary" @click="updateVideoLoc(video.src)">Select</button></td>
              <td><button type="button" class="btn btn-danger" @click="updateVideoLoc(video.src)">Delete</button></td>
            </tr>
          </tbody>
          </table>
        </div>
        <div class="col-8">
          <div class="row">
            <div class="col">
              <video :key="currentVideo" controls>
                <source :src="currentVideo" type="video/mp4">
              </video>
            </div>
          </div>
            <div class="row">
              <div class="col">
                <div id="carouselExampleIndicators" class="carousel slide" data-bs-ride="carousel">
                  <div class="carousel-indicators">
                    <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="0" class="active" aria-current="true" aria-label="Slide 1"></button>
                    <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="1" aria-label="Slide 2"></button>
                    <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="2" aria-label="Slide 3"></button>
                  </div>
                  <div class="carousel-inner">
                    <div class="carousel-item active">
                      <img src="@/assets/logo.png" class="image-size" alt="...">
                    </div>
                    <div class="carousel-item">
                      <img src="@/assets/logo.png" class="image-size" alt="...">
                    </div>
                    <div class="carousel-item">
                      <img src="@/assets/logo.png" class="image-size" alt="...">
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
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
<script>
import { usemediaStore } from '@/store/mediaStore'
import {ref} from 'vue'
export default {
  setup() {
    let mediaStore = usemediaStore() 
    let currentVideo = ref('C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/hiveVideos/Angry_Cat.mov')
    return {mediaStore, currentVideo}
  },
  data() {
    return {
      theme: 'dark-theme',
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
      },
      Theme: function () {
        return this.theme
      }
    }
}
</script>
<style>
video {
  height: 47vh;
}
.image-size {
  height: 47vh;
}
</style>
<style lang="scss">
@import '@/assets/scss/custom.scss';
</style>