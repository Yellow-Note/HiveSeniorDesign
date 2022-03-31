<template>
  <div class="Queue">
    <h1>This is our Queue page</h1>
    <!-- <iframe src="C:\Users\pyrodraco\Desktop\COSC\SeniorProject\vueapp\hive2\public\hiveVideos\DRONE.mp4"></iframe> -->
    <div>
      <div v-for="(video, index) in videos" :key="video.videoName">
      <button type="button" class="btn btn-dark" @click="updateVideoLoc(index)">{{video.videoName}}</button>
      </div>
    </div>
    <div v-for="video in videos" :key="video">
      <video width="1280" height="720" controls>
        {{video.videoName}}
        <source :src="updateSrc">
      </video>
    </div>
  </div>
</template>
<script>
export default {
data() {
        return {
            setIndex: 0,
            videos: [
              {
                videoName: 'video1',
                videoLocation: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/hiveVideos/DRONE.mp4'
              },
              {
                videoName: 'video2',
                videoLocation: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/hiveVideos/DRONE.mp4'
              },
              {
                videoName: 'video3',
                videoLocation: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/hiveVideos/DRONE.mp4'
              },
              {
                videoName: 'video4',
                videoLocation: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/hiveVideos/DRONE.mp4'
              },
            ]
        }
    },
    computed: {
      updateSrc() {
        return this.videos[this.setIndex][1]
      }
    }, 
    methods: {
      updateVideoLoc(index){
        this.setIndex = index
      }
    }
}
</script>