import { defineStore } from 'pinia'

export const usemediaStore = defineStore('media', {
    state: () => ({
        videos: [
            {
                timestamp: '12-10-2021 13:15',
                src: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/hiveVideos/DRONE.mp4',
                alertedImages: [
                    {
                        imageName: '13:16:59',
                        url: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture1.jpg',
                        gps: {
                            lat: 41.1585,
                            lng: -105.370
                        }
                    },
                        {
                        imageName: '13:18:59',
                        url: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture2.jpg',
                        gps: {
                            lat: 41.1544,
                            lng: -105.3745
                        }
                    }
                ],
                slicedImages: [
                    {
                        imageName: '13:16:59',
                        url: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture1.jpg',
                        gps: {
                            lat: 41.1585,
                            lng: -105.370
                        }
                    },
                    {
                        imageName: '13:18:59',
                        url: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture2.jpg',
                        gps: {
                            lat: 41.1585,
                            lng: -105.370
                        }

                    }
                ]
            },
            {
                timestamp: '12-13-2021 14:45',
                src: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/hiveVideos/Angry_Cat.mov',
                alertedImages: [
                    {
                        imageName: '14:46:59',
                        url: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture3.jpg',
                        gps: {
                            lat: 41.1585,
                            lng: -105.370
                        }
                    }
                ],
                slicedImages: [
                    {
                        imageName: '13:16:59',
                        url: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture3.jpg',
                        gps: {
                            lat: 41.1585,
                            lng: -105.370
                        }
                    }
                ]
            },
            {
                timestamp: '12-15-2021 16:45',
                src: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/hiveVideos/Angry_Cat.mov',
                alertedImages: [
                    {
                        imageName: '16:46:59',
                        url: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture3.jpg',
                        gps: {
                            lat: 41.1585,
                            lng: -105.370
                        }
                    }
                ],
                slicedImages: [
                    {
                        imageName: '16:16:59',
                        url: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture3.jpg',
                        gps: {
                            lat: 41.1585,
                            lng: -105.370
                        }
                    }
                ]
            } 
        ]
    }),
  getters: {
    
  },
  actions: {

  },
})